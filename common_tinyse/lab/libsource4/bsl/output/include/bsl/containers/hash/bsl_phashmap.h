/***************************************************************************
 * 
 * 
 **************************************************************************/
 
 
 
/**
 * @file phashmap.h
 * @brief 
 *  
 **/


#ifndef  __BSL_PHASHMAP_H_
#define  __BSL_PHASHMAP_H_

#include <bsl/containers/hash/bsl_phashtable.h>

namespace bsl
{

template <class _Key, /*��Ϊhashkey������*/
		 class _Value,	/*��Ϊhash value������*/
		 /**
		  * hash �����ķº���������
		  * struct xhash {
		  * 	inline size_t operator () (const _Key &_1);
		  * };
		  **/
		 class _HashFun = xhash<_Key>,
		 /**
		  * �ж�����key��ȵķº���
		  * ���� struct equal {
		  * 	inline bool operator () (const _Tp &_1, const _Tp &_2);
		  * };
		  */
		 class _Equl = std::equal_to<_Key>,	
		 /**
		  * �ռ��������Ĭ�ϵĿռ�������ܹ���Ч�ʵĹ���С�ڴ棬��ֹ�ڴ���Ƭ
		  * �����������������ڲ����ͷ�������ڴ�
		  *
		  * bsl_alloc<_Key>���ڴ���������������������������ͷ��ڴ棬
		  * ���ǲ�����Ч��ֹ�ڴ���Ƭ
		  */
		 class _InnerAlloc = bsl_sample_alloc<bsl_alloc<_Key>, 256>
		>
class phashmap : public bsl_phashtable<_Key, std::pair<_Key, _Value>, _HashFun, _Equl, 
	bsl::pair_first<std::pair<_Key, _Value> >, _InnerAlloc>
{
public:
	typedef std::pair<_Key, _Value> _Pair;
	typedef phashmap<_Key, _Value, _HashFun, _Equl, _InnerAlloc> _Self;
	typedef bsl_phashtable<_Key, _Pair, _HashFun, _Equl, bsl::pair_first<_Pair>, _InnerAlloc> _Base;
	typedef typename _Base::iterator iterator;
	typedef typename _Base::const_iterator const_iterator;

	typedef _Value value_type;
	typedef _Key key_type;

private:
	_Self & operator = (const _Self &) { return  *this; }
public:
	/**
	 * create�����ο�phashtable�ķ���,ֱ�Ӽ̳�
	 * destroy����Ҳֱ�Ӽ̳�
	 */

	/**
	 * @brief ����ָ��key��ȡvalueֵ
	 *
	 * @param [in/out] k   : const key_type&	ָ���Ĳ���key
	 * @param [in/out] val   : value_type*	��ȡ��valueֵ�Ĵ洢��ַ
	 * 				���value��Ϊ�գ���*val��ֵ���ҵ�ֵ
	 * @return  int 
	 *				���� HASH_EXIST		��ʾhashֵ����
	 *				���� HASH_NOEXIST	��ʾhashֵ������
	 * @retval   
	 * @see 
	**/
	int get(const key_type &k, value_type *val = 0) const {
		return _Base::get_map(k, val);
	}
	int get(const key_type &k, value_type *val = 0) {
		return _Base::get_map(k, val);
	}

	/**
	 * @brief ��key �� value �� ���� hash����
	 *
	 * @param [in/out] k   : const key_type&	keyֵ	
	 * @param [in/out] val   : const value_type&	valueֵ
	 * @param [in/out] flag   : int	
	 * 				flag ����0�����ֵ����ֱ�ӷ��أ�
	 * 				��0��ʾ�����ֵ���ڣ��滻��ֵ
	 * @return  int 	
	 *  			����	-1	��ʾset���ó���, (�޷������½��)
	 * 			��������ʾ����ɹ�������ɹ�����������״̬
	 * 				����	HASH_OVERWRITE	��ʾ���Ǿɽ��ɹ�(��flag��0��ʱ�򷵻�)
	 * 				����	HASH_INSERT_SEC	��ʾ�����½��ɹ�
	 * 				����	HASH_EXIST	��ʾhash��������(��flagΪ0��ʱ�򷵻�)
	 * @retval   
	 * @see 
	**/
	int set(const key_type &k, const value_type &val, int flag = 0) {
		return _Base::set(k, _Pair(k, val), flag);
	}

	/**
	 * @brief ����ָ����keyɾ�����
	 *
	 * @param [in/out] k   : const key_type&
	 * @return  int 
	 * 		����	HASH_EXIST��ʾ�����ڲ�ɾ���ɹ�
	 * 		����	HASH_NOEXIST��ʾ��㲻���ڲ���ɾ��
	 * @retval   
	 * @see 
	**/
	int erase(const key_type &k) {
		return _Base::erase(k);
	}
};

};


#endif  //__PHASHMAP_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */