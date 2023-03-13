#ifndef ARRAY_H
#define ARRAY_H

#include <stdexcept>

template <class T>
class Array
{
	private:
		T *array;
		size_t bytes;

	public:
		Array(size_t p_bytes = 0) {
			bytes = p_bytes;
			array = new T[p_bytes];
			for(size_t i = 0; i < bytes; i++) {
				array[i] = 0;
			}
		}

		Array(const Array<T>& p_array) {
			bytes = p_array.bytes;
			array = new T[bytes];
			for(size_t i = 0; i < bytes; i++) {
				array[i] = p_array[i];
			}
		}

		~Array() { delete []array; }

		size_t size() const {
			return bytes;
		}

		bool empty() const {
			return !(bytes > 0);
		}

		void push(const T& p_element) {
			for(size_t i = 0; i < bytes; i++) {
				if(!array[i]) {
					array[i] = p_element;
					return; //Saves the element and exits
				}
			}
			_push(p_element); //Not enough space to save the element
		}

		void _push(const T& p_element) {
			T *_array = new T[bytes++]; // Creates new array to fit new element
			for(size_t i = 0; i < bytes-1; i++) {
				_array[i] = array[i]; // Copies the old array to the new one
			}
			_array[bytes-1] = p_element; // Copies new element at first
			delete []array;
			array = _array; // Links new array to the old pointer
		}

		T pull(const int index) {
			T element = get(index);
			T *_array = new T[bytes--];

			for(size_t i = 0; i < index; i++) {
				_array[i] = array[i];
			}
			for(size_t i = index+1; i < bytes+1; i++) {
				_array[i-1] = array[i];
			}

			delete []array;
			array = _array;
			return element;
		}

		const T& get(const int index) const {
			if(abs(index) >= (int)bytes) {
				throw std::out_of_range("Index bigger than the array.");
			}
			else if(index < 0) {
				return array[bytes+index];
			}

			return array[index];
		}

		const T& operator [](const int index) const {
			return get(index);
		}

		T& operator [](const int index) {
			return const_cast<T&>(const_cast<const Array*>(this)->get(index));
		}

		bool operator ==(const Array<T>& right) const {
			if(bytes != right.bytes) {
				return false;
			}

			for(size_t i = 0; i < bytes-1; i++) {
				if(array[i] != right[i]) {
					return false;
				}
			}
			return true;
		}

		bool operator !=(const Array<T>& right) const {
			return !(this == right);
		}

		friend std::ostream& operator <<(std::ostream& out, const Array& p_array) {
			size_t i;
			out << "[";
			for(i = 0; i < p_array.bytes-1; i++) {
				out << p_array[i] << ", ";
			}
			out << p_array[i] << "]";

			return out;
		}
};

#endif // ARRAY_H