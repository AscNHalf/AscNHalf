/* AscNHalf */

#ifndef _FASTQUEUE_H
#define _FASTQUEUE_H

/** dummy lock to use a non-locked queue.
 */
class DummyLock
{
public:
	INLINE void Acquire() { }
	INLINE void Release() { }
};

/** linked-list style queue
 */
template<class T, class LOCK>
class FastQueue
{
	struct node
	{
		T element;
		node * next;
	};

	node * last;
	node * first;
	LOCK m_lock;

public:

	FastQueue()
	{
		last = 0;
		first = 0;
	}

	~FastQueue()
	{
		Clear();
	}

	void Clear()
	{
		// clear any elements
		while(last != 0)
			Pop();
	}

	void Push(T elem)
	{
		m_lock.Acquire();
		node * n = new node;
		if(last)
			last->next = n;
		else
			first = n;

		last = n;
		n->next = 0;
		n->element = elem;
		m_lock.Release();
	}

	T Pop()
	{
		m_lock.Acquire();
		if(first == 0)
		{
			m_lock.Release();
			return reinterpret_cast<T>(0);
		}
        
		T ret = first->element;
		node * td = first;
		first = td->next;
		if(!first)
			last = 0;

		delete td;
		m_lock.Release();
		return ret;
	}

	T front()
	{
		m_lock.Acquire();
		if(first == 0)
		{
			m_lock.Release();
			return reinterpret_cast<T>(0);
		}

		T ret = first->element;
		m_lock.Release();
		return ret;
	}

	void pop_front()
	{
		m_lock.Acquire();
		if(first == 0)
		{
			m_lock.Release();
			return;
		}

		node * td = first;
		first = td->next;
		if(!first)
			last = 0;

		delete td;
		m_lock.Release();
	}

	bool HasItems()
	{
		bool ret;
		m_lock.Acquire();
		ret = (first != 0);
		m_lock.Release();
		return ret;
	}
};

#endif
