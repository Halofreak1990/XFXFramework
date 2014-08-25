/*
** Copyright 2001, Travis Geiselbrecht. All rights reserved.
** Distributed under the terms of the NewOS License.
*/
/*
 * Copyright (c) 2008 Travis Geiselbrecht
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <sys/types.h>

#include <System/Types.h>

#include "ethernet.h"

#define MIN_ARP_SIZE 28


typedef struct arp_packet {
	uint16_t hard_type;
	uint16_t prot_type;
	uint8_t  hard_size;
	uint8_t  prot_size;
	uint16_t op;
	ethernet_addr sender_ethernet;
	ipv4_addr sender_ipv4;
	ethernet_addr target_ethernet;
	ipv4_addr target_ipv4;
} PACKED arp_packet;

enum
{
	ARP_OP_REQUEST = 1,
	ARP_OP_REPLY,
	ARP_OP_RARP_REQUEST,
	ARP_OP_RARP_REPLY
};

enum
{
	ARP_HARD_TYPE_ETHERNET = 1
};

typedef struct arp_cache_entry
{
	struct arp_cache_entry *next;
	struct arp_cache_entry *all_next;
	ipv4_addr ip_addr;
	netaddr link_addr;
	time_t last_used_time;
} arp_cache_entry;

// arp cache
static void *arp_table;
static mutex_t arp_table_mutex;
static arp_cache_entry *arp_cache_entries;

typedef struct arp_wait_request
{
	struct arp_wait_request *next;
	ipv4_addr sender_ipaddr;
	ipv4_addr ip_addr;
	time_t last_attempt_time;
	int attempt_count;
	void (*callback)(int code, void *, ifnet *, netaddr *);
	void *callback_args;
	ifnet *i;
} arp_wait_request;

// list of threads blocked on arp requests
static arp_wait_request *arp_waiters;
static mutex_t arp_wait_mutex;
static event_t arp_wait_event;

static int arp_cache_compare(void *_e, const void *_key)
{
	arp_cache_entry *e = (arp_cache_entry *)_e;
	const ipv4_addr *addr = (const ipv4_addr *)_key;

	return (e->ip_addr == *addr) ? 0 : 1;
}

static unsigned int arp_cache_hash(void *_e, const void *_key, unsigned int range)
{
	arp_cache_entry *e = (arp_cache_entry *)_e;
	const ipv4_addr *key = (const ipv4_addr *)_key;
	const ipv4_addr *addr;

	if(e)
		addr = &e->ip_addr;
	else
		addr = key;

	// XXX make this smarter
	return ((*addr) ^ (*addr >> 8) ^ (*addr >> 16) ^ (*addr >> 24)) % range;
}


