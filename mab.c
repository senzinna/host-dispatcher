// Scott Enzinna
// 11/26/13
// mab.c 

#include "mab.h"

// Check memory
MabPtr memChk(MabPtr m, int size)
{
	while(m)
	{
		if (size <= (*m).size)
		{
			if ((*m).allocated == 0)
			{
				return m;
			}
		}
		m = (*m).next;
	}
	return NULL;
}

// Initialise
MabPtr memInitialise( int offset, int size)
{
	MabPtr m = malloc(sizeof(Mab));
	(*m).offset = offset;
	(*m).size = size;
	(*m).allocated = 0;
	(*m).next = (*m).prev = NULL;
	
	return m;
}


// Merge memory
MabPtr memMerge(MabPtr m)
{
	MabPtr left = (*m).prev;
	MabPtr right = (*m).next;
	MabPtr temp;
	
	// left node
	if (left)
	{
		if ((*left).allocated ==0)
		{
			temp = m;
			m = left;
			(*m).size = (*m).size + (*temp).size;
			
			if ((*m).next == (*temp).next)
			{
				(*(*m).next).prev = m;
			}
		free(temp);
		temp = NULL;
		}
	}
	
	// right node
	if (right)
	{
		if ( !(*right).allocated)
		{
			temp = right;
			(*m).size = (*m).size + (*temp).size;
			
			if((*m).next == (*temp).next)
			{
				(*(*m).next).prev = m;
			}
		free (temp);
		temp = NULL;
		return m;
		}
	}
	return m;
}

// Free memory
MabPtr memFree(MabPtr m)
{
	if (m)
	{
		; // Do nothing
	}
	else if (!m)
	{
		return NULL;
	}
	
	if ( !(*m).prev && !(*m).next )
	{
		free(m);
		m = NULL;
	}
	else
	{
		(*m).allocated = 0;
		m = memMerge(m);
	}
	return m;
}

// Split memory
MabPtr memSplit(MabPtr m, int size)
{
	MabPtr right = malloc(sizeof(Mab));
	
	if (m)
	{
		; // do nothing
	}
	else if (!m)
	{
		return NULL;
	}

	int temp;
	int tp;
	
	temp = (*m).offset + size;
	tp = (*m).size - size;
	right = memInitialise(temp,tp);
	
	(*m).size = size;
	(*m).allocated = 1;
	
	(*right).prev = m;
	
	if ((*m).next)
	{
		(*right).next = (*m).next;
		right = memMerge(right);
	}
	(*m).next = right;
	
	return m;
}

// Memory alloc
MabPtr memAlloc(MabPtr m, int size)
{
	int temp;
	temp = (*m).size;
	
	if (temp < size)
	{
		return NULL;
	}
	
	if (temp > size)
	{
		m = memSplit(m, size);
	}
		
	(*m).allocated = 1;
	return m;
}







