#include "smart_ptr.h"
#include <memory>
#include <iostream>

class foo;
class Test
{
public:
    Test()
    {
        std::cout << "construct.." << std::endl;
    }

    void method()
    {
        std::cout << "welcome Test.." << std::endl;
    }

    ~Test()
    {
        std::cout << "destruct.." << std::endl;
    }

public:
    std::weak_ptr<foo> fooptr;
};

class foo
{
public:
    foo()
    {
        std::cout << "foo construct.." << std::endl;
    }

    void method()
    {
        std::cout << "welcome Test foo.." << std::endl;
    }

    ~foo()
    {
        std::cout << "foo destruct.." << std::endl;
    }

public:
    std::weak_ptr<Test> testptr;
};


class Bad
{
public:	
    std::shared_ptr<Bad> getptr() 
    {		
        //
        return std::shared_ptr<Bad>(this);	
    }	

    ~Bad() 
    { 
        std::cout << "Bad::~Bad() called" << std::endl; 
    }
};




int main()
{
    // 基本测试
    // Test* t1 = new Test();

    // _SMART_PTR shared_ptr<Test> shptr(t1);

    // _SMART_PTR shared_ptr<Test> shptr1(shptr);

    // _SMART_PTR shared_ptr<Test> shptr2 = shptr1;

    // std::cout << "RefCount: " << shptr2.getRefCount() << std::endl;

    // shptr2->method();

    // (*shptr2).method();

    // if (shptr2)
    // {
    //     std::cout << "ptr is exit " << std::endl;
    // }

    // 循环引用 测试
    Test* t2 = new Test();
    foo* foo1 = new foo();

    std::shared_ptr<Test> shptr_Test(t2);
    std::shared_ptr<foo>  shptr_foo(foo1);

    std::cout << "shptr_Test RefCount: " << shptr_Test.use_count() << std::endl;
    std::cout << "shptr_foo RefCount: " << shptr_foo.use_count() << std::endl;

    shptr_Test->fooptr = shptr_foo;
    shptr_foo->testptr = shptr_Test;
      
    std::cout << "shptr_Test RefCount: " << shptr_Test.use_count() << std::endl;
    std::cout << "shptr_foo RefCount: " << shptr_foo.use_count() << std::endl;



    // std::weak_ptr
    // foo* foo2 = new foo();

    // // share_ptr 管理对象
    // std::shared_ptr<foo> shptr_foo2(foo2);

    // // weak_ptr 得到临时所有权
    // std::weak_ptr<foo> weak_foo2(shptr_foo2);

    // // 如果要获取数据指针，需要通过lock接口获取
    // weak_foo2.lock()->method();

    // std::shared_ptr<foo> tmp =  weak_foo2.lock();

    // std::cout << "shptr_foo2 RefCount: " << weak_foo2.lock().use_count() << std::endl;

    // std::cout << "shptr_foo2 RefCount: " << shptr_foo2.use_count() << std::endl;

    // std::cout << "weak_foo2 RefCount: " << weak_foo2.use_count() << std::endl;



    // _SMART_PTR weak_ptr
    // share_ptr 管理对象

    // foo* foo4 = new foo();

    // _SMART_PTR shared_ptr<foo> shptr_foo4(foo4);

    // std::cout << "shptr_foo4 RefCount: " << shptr_foo4.getRefCount() << std::endl;

    // // weak_ptr 得到临时所有权
    // _SMART_PTR weak_ptr<foo> weak_foo4(shptr_foo4);

    // std::cout << "shptr_foo4 RefCount: " << weak_foo4.use_count() << std::endl;

    // // 如果要获取数据指针，需要通过lock接口获取
    // weak_foo4.lock()->method();

    // std::cout << "eak_foo4.lock()->method(); RefCount: " << weak_foo4.use_count() << std::endl;

    // _SMART_PTR shared_ptr<foo> tmp =  weak_foo4.lock();

    // std::cout << "shptr_foo4 RefCount: " << weak_foo4.lock().getRefCount() << std::endl;
    // std::cout << "shptr_foo4 RefCount: " << shptr_foo4.getRefCount() << std::endl;
    // std::cout << "weak_foo4 RefCount: " << weak_foo4.use_count() << std::endl;


   // std::shared_ptr<Bad> bp1(new Bad());
   // bp1->getptr();	
   // std::shared_ptr<Bad> bp2 = bp1->getptr();	// 打印bp1和bp2的引用计数	
    //std::cout << "bp1.use_count() = " << bp1.use_count() << std::endl;	
    //std::cout << "bp2.use_count() = " << bp2.use_count() << std::endl;

    // https://www.zhihu.com/question/30957800

    return 0;
}
