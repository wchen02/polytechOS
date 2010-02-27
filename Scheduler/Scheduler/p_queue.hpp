/*#ifndef P_QUEUE_H
#define P_QUEUE_H
#include <algorithm>
template<class T, class Comparable1, class Comparable2>
class p_queue{

public:
	p_queue(size_t capacity){
		_capacity = capacity;
		_size = 0;
		_container = new T[ _capacity ];
	}
	p_queue(){
		_capacity = 10;
		_size = 0;
		_container = new T[ _capacity ];
	}

	void push_back( const T & object ) {
		_size++;
		if(_size == _capacity){
			T* tmp = new T[ _capacity ];
			for(size_t i = 0; i < _capacity-1; ++i){
				tmp[i] = _container[i];
			}
			_capacity *= 2;     // square the capacity if full
			_container =new T[ _capacity ];
			for( size_t i = 0; i < _capacity; ++i ){
				_container[i] = tmp[i];
			}
		}
		_container[ _size ] = object;
		std::sort( _container, _container + _size, Comparable2( ) ); // in case they have the same priorit
		sort( _container, _container + _size, Comparable1( ) );      // Highest priority sorting

	}

	T  pop_front( ){
		if( 0 <= _size){
			T tmp = _container[0];
			std::swap( _container[0], _container[ _size ]);
			_size--;
			//delete _container[ _size + 1 ]; // delete the old one
			return tmp;
		}
		return T();
	}

	T front( ){
		T tmp;
		if( 0 <= _size )
			tmp = _container[0];
		return tmp;
	}

	size_t size() const {
		return _size;
	}


	T& operator[]( size_t i ){
		if( i <= _size )
			return _container[i] ;
	}
	
	
	void removeIndex( size_t i ){
		if( 0 <= _size ){
			std::swap( _container[i], _container[ _size ]);
			_size--;
		}
	}
private:
	size_t _capacity;
	size_t _size;
	T* _container;
};






#endif*/
