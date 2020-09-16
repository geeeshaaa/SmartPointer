#include <iostream>
using namespace std;
template<class T>
class UniquePtr {
	T* ptr;
public:
	UniquePtr() :ptr(0){}
	UniquePtr(T* ptr):ptr(ptr){}
	UniquePtr(const UniquePtr& ptr) = delete;
	T* operator=(const UniquePtr& ptr) = delete;
	void Release() { ptr = nullptr; }
	~UniquePtr() { delete ptr; }
};

template<class T>
class SharedPtr {
	T* ptr;
	int* count;
public:
	SharedPtr() { ptr = 0; count = new int(0); }
	SharedPtr(T* ptr):ptr(ptr),count(new int(1)){}
	SharedPtr(const SharedPtr& ptr);
	~SharedPtr();
	int Use_Count() { return *count; }
	void Reset();
	T* Get() { return ptr; }
	void Swap(SharedPtr& ptr);
	T& operator *() { return *ptr; }
	T* operator =(const SharedPtr& ptr);
};

template<class T>
SharedPtr<T>::SharedPtr(const SharedPtr& ptr)
{
	this->ptr = ptr.ptr;
	count = ptr.count;
	*count += 1;
}

template<class T>
SharedPtr<T>::~SharedPtr()
{
	if (*count <= 1) {
		delete ptr;
		delete count;
	}
	else {
		*count -= 1;
	}
}

template<class T>
void SharedPtr<T>::Reset()
{
	ptr = nullptr;	*count -= 1;	count = new int(0);
}

template<class T>
void SharedPtr<T>::Swap(SharedPtr& ptr)
{
	T* Ttemp = ptr.ptr;
	int* temp = ptr.count;
	ptr.ptr = this->ptr;
	ptr.count = this->count;
	this->ptr = Ttemp;
	this->count = temp;
}

template<class T>
T* SharedPtr<T>::operator=(const SharedPtr& ptr)
{
	if (*count > 1) {
		this->ptr = ptr.ptr;
		count = ptr.count;
		*count += 1;
	}
	else {
		delete this->ptr;
		delete this->count;
		this->ptr = ptr.ptr;
		count = ptr.count;
		*count += 1;
	}
	return this->ptr;
}

int main()
{
	SharedPtr<int> p1(new int(456));
	SharedPtr<int> p2 = new int(1);
	SharedPtr<int> p3 = new int[] {8, 9, 10};
	SharedPtr<int> p4;
	SharedPtr<int> p5(p2);
	SharedPtr<int> p6 = p3;
	p5.Reset();

	p3 = p1;
	p1.Swap(p2);
	cout << "p1 use_count: " << p1.Use_Count() << endl;
	cout << "p2 use_count: " << p2.Use_Count() << endl;
	cout << "p3 use_count: " << p3.Use_Count() << endl;
	cout << "p4 use_count: " << p4.Use_Count() << endl;
	cout << "p5 use_count: " << p5.Use_Count() << endl;
	cout << "p6 use_count: " << p6.Use_Count() << endl;


	cout << "p6 Get: " << p6.Get() << endl;

	shared_ptr<int> sh(new int[] {1, 2, 3, 4, 5});
	shared_ptr<int> sh1;
	sh1 = sh;
	cout << "sh use: " << sh.use_count() << endl;
	sh.reset();
	cout << "sh use: " << sh.use_count() << endl;
	cout << "sh get: " << sh1;
	



	UniquePtr<int> uptr1(new int(1));
	UniquePtr<int> uptr2(new int(2));
	UniquePtr<int> uptr3(new int(3));
	//UniquePtr<int> uptr4(uptr1);
	UniquePtr<int> uptr5;
	//uptr5 = uptr1;
	uptr3.Release();
	

	unique_ptr<int> unique(new int(22));
	unique.release();

}
