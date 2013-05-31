// Copyright (C) XFX Team
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright 
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright 
//       notice, this list of conditions and the following disclaimer in the 
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of any 
//       contributors may be used to endorse or promote products derived from 
//       this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.

#include <GameComponentCollection.h>

namespace XFX
{
	GameComponentCollection::GameComponentCollection()
	{
	}

	GameComponentCollection::~GameComponentCollection()
	{
	}

	void GameComponentCollection::ClearItems()
	{
		_components.Clear();
	}

	int GameComponentCollection::Count() const
	{
		return _components.Count();
	}

	int GameComponentCollection::GetType() const
	{
	}

	void GameComponentCollection::InsertItem(int index, IGameComponent* item)
	{
		_components.Insert(index, item);

		ComponentAdded(this, new GameComponentCollectionEventArgs(item));
	}

	void GameComponentCollection::RemoveItem(int index)
	{
		IGameComponent* component = _components[index];

		_components.RemoveAt(index);

		ComponentRemoved(this, new GameComponentCollectionEventArgs(component));
	}

	void GameComponentCollection::SetItem(int index, IGameComponent* item)
	{
		_components[index] = item;
	}

	GameComponentCollectionEventArgs::GameComponentCollectionEventArgs(IGameComponent* gameComponent)
	{
		_gameComponent = gameComponent;
	}

	IGameComponent* GameComponentCollectionEventArgs::getGameComponent() const
	{
		return _gameComponent;
	}

	int GameComponentCollectionEventArgs::GetType() const
	{
	}

	IGameComponent* GameComponentCollection::operator[](const int index)
	{
		return _components[index];
	}
}
