#pragma once

//---------------------------------------------------------------------------------------
class AFX_EXT_CLASS KList
{
public:
	KList(void);
	virtual~KList(void);

	//---------------------------------
	//iterator¿‡∂®“Â
	class iterator
	{
	public:
		iterator(void*pMember=NULL)
		{
			m_pMember=pMember;
			m_pNext=this;
			m_pPrev=this;
		}
		virtual~iterator(void)
		{
		}
	public:
		void operator ++()
		{
			*this=*m_pNext;
		}
		void operator --()
		{
			*this=*m_pPrev;
		}
		void* operator *()
		{
			return m_pMember;
		}
		iterator &operator =(iterator titerator)
		{
			m_pMember=titerator.m_pMember;
			m_pNext=titerator.m_pNext;
			m_pPrev=titerator.m_pPrev;
			return (*this);
		}
		bool operator ==(iterator titerator)
		{
			return (m_pMember==titerator.m_pMember &&
					m_pNext==titerator.m_pNext &&
					m_pPrev==titerator.m_pPrev);
		}
		bool operator !=(iterator titerator)
		{
			return (m_pMember!=titerator.m_pMember ||
					m_pNext!=titerator.m_pNext ||
					m_pPrev!=titerator.m_pPrev);
		}
	protected:
		void*		m_pMember;
		iterator*	m_pNext;
		iterator*	m_pPrev;

		friend class KList;
	};

	KList::iterator begin(void);
	KList::iterator end(void);
	void* front(void);
	void pop_front(void);
	void push_front(void*ptr);
	void* back(void);
	void pop_back(void);
	void push_back(void*ptr);
	void insert(KList::iterator titerator,void* ptr);
	void erase(KList::iterator titerator);
	unsigned long size(void);
	bool empty(void);
	void clear(void);
	void remove(void* ptr);
	KList::iterator find(void* ptr);

protected:
	iterator		m_iterator;
	unsigned long	m_ulSize;
};

