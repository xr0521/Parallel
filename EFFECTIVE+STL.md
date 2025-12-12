# EFFECTIVE+STL

```C++
template<typename T>
bool lastGreaterThanFirst(const T& contain) {
    if (contain.empty()) return false;
    typename T::const_iterator first(contain.begin());
	typename T::const_iterator end(contain.end());
    return *--end > *first;
}
//属于模板代码，在模板中访问嵌套类型 T::const_iterator 时，必须加 typename，否则编译器无法判断它是否为类型
```

## 第一章 容器

### 序列容器

#### vector

特点： vector容器属于动态数组、元素是以连续内存进行存储的、随机访问O（1）、可与C风格进行交互(data())、在末尾插入删除为O(1)、在中间插入删除时间复杂度为O（n）、可动态扩容

使用场景:  适用于随机访问、按索引进行访问、需要与C风格接口进行传递内存、适用于在末尾进行删除等操作

常用方法：

```C++
void vectorExample() {
    //构造方法
    std::vector<int> vec_int;//默认构造
	std::vector<int> vec_int2(10);//指定大小构造，默认值为0
	std::vector<int> vec_int3(10, 5);//指定大小和默认值构造
	std::vector<int> vec_int4{ 1,2,3,4,5 };//列表初始化
    std::vector<int> vec_int5(vec_int4.begin()+3, vec_int4.end());//区间构造
	std::vector<int> vec_int6 = vec_int4;//拷贝构造
    //遍历方法
    for (const auto&x:vec_int5 ) {
		std::cout << x << " ";
    }
    std::cout << std::endl;
    //只读迭代器遍历
    for (std::vector<int>::const_iterator it = vec_int5.begin(); it != vec_int5.end();++it) {
		std::cout << *it << " ";
    }
	std::cout << std::endl;
    //修改迭代器遍历
    for (std::vector<int>::iterator it = vec_int5.begin(); it != vec_int5.end(); ++it) {
        *it += 10;
        std::cout << *it << " ";
	}
    //遍历方法
    for (const auto& x : vec_int5) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    //数组大小 size/empty
    std::cout << "Size:" << vec_int2.size() << std::endl;
    if (!vec_int2.empty()) {
        std::cout << "Vec is not Empty()" << std::endl;
		//operator[]/at区别  operator[]不进行边界检查，at进行边界检查
        /*vec_int2[10] = 0;//直接终止程序
        vec_int2.at(10) = 100; //会抛出异常*/
        //front / back O(1);
		std::cout << "First Element:" << vec_int2.front() << std::endl;
        //data() 返回底层指针数组'
        auto ptr = vec_int5.data();
        std::cout << *ptr << std::endl;
		//push_back / pop_back O(1)均摊复杂度 push_back支持移动语义
        vec_int5.push_back(100);
        std::cout << "After push_back 100:" << vec_int5.back() << std::endl;
        vec_int5.pop_back();
		//vector容器没有push_front/pop_front
		//emplace_back O(1)均摊复杂度 直接在容器尾部构造元素，避免拷贝或移动开销
        vec_int5.emplace_back(520);
		//emplace O(n) 直接在指定位置构造元素
        vec_int5.emplace(vec_int5.begin(), 521);
		//insert O(n) 在指定位置插入元素，支持移动语义
		vec_int5.insert(vec_int5.begin(), 522);
        //erase O(n) 删除指定位置元素
		vec_int5.erase(vec_int5.begin());
        for (const auto& x : vec_int5) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
        vec_int5.resize(0);//将调整整个数组大小
        vec_int5.reserve(3);//只负责“扩容”，不负责“缩容”或“裁剪数据”
        for (const auto& x : vec_int5) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
    }
}

```

#### string

特点: 表面像容器也像类  std::basic_stding<char> 满足连续内存要求、提供字符串专用操作:

查找、子串、拼接、格式化（部分）、c_str() 等、可视为容器 + 文本处理工具的混合体。

适用场景:  处理文本数据，字符串拼接、查找、子串等

常用方法:

```C++
void stringExample() {
    //构造方式
	std::string str1;//默认构造
	std::cout << "str1 size:" << str1.size() << std::endl;
	std::string str2("Hello, World!");//C风格字符串构造
    std::string str3(5, 'x');
    std::cout << str3 << std::endl;
	char c[] = { 'H','e','l','l','o','\0'};
	std::string str4(c);//指定长度构造
    std::cout << str4 << std::endl;
	std::string str5(str2);//拷贝构造
	//遍历方法
    for (const auto& c:str2) {
		std::cout << c << " ";
    }
	std::cout << std::endl;

    for (std::string::const_iterator it = str2.begin(); it != str2.end();++it) {
        std::cout << *it << " ";
	}
    for (std::string::iterator it = str2.begin(); it != str2.end(); ++it) {
        std::cout << (char)(*it - 32) << " ";
    }
    std::cout << std::endl;
    //拼接
	str1 += "Hello";
    std::cout << "str1= " << str1 << std::endl;
	str1.append(c); //适用于string  char数组以及string对象
    str1.assign(str5.begin(), str5.end());
    std::cout << "str1= " << str1 << std::endl;
    auto ss = str5.data();
	std::cout << ss << std::endl;
    //返回字串
	std::string sss = str5.substr(1, 5); //从索引1开始，长度为5的子串
    std::cout << "sss=" << sss << std::endl;
	//find/rfind O(n)
    auto pos = str5.find("Hello");
    if (pos != std::string::npos) {
        std::cout << "'World' found at position: " << pos << std::endl;
    }
    else {
        std::cout << "'World' not found" << std::endl;
	}
	str5.rfind("o");//refind是从后往前找
    str5.insert(5, "!");
    str5.erase(6,8);
    str5.reserve(3);
    std::cout << "str5= " << str5 << std::endl;
}
```

#### deque

特点: 支持高效的头尾双插、支持随机访问operator[]、中间频繁插入/删除仍然O（n）

适用场景: 需要频繁在头尾进行插入删除，同时仍需按索引访问的场合，不能保证连续内存

常用方法:

**push_front(v) / push_back(v) 摊销 O(1)**

**pop_front() / pop_back() O(1)**

**operator[] / at 随机访问 O(1)**

**insert / erase 中间位置 O(n)**

**size() / empty() / clear()**

**emplace_front / emplace_back**

**front() / back()**

#### list

特点:  双向链表实现，**每个元素单独分配结点**（非连续）。

插入/删除任意位置 O(1)（给定迭代器），不需要移动其他元素。

随机访问 O(n)（不支持 `operator[]`）。

迭代器在插入/删除其他结点时通常保持有效（对删除的迭代器除外）

**适用场景**

- 需要在容器中间频繁插入/删除，并且操作都是已知位置（用迭代器定位）的场景。
- 需要稳定的引用/指针/迭代器（不受其他位置插入影响）。

**常用方法**

```C++
void listExample() {
    //构造方式
    std::list<int> list;//默认构造
    std::list<int> list_2(5, 6);
    std::list<int> list_3={ 1,2,3 };
    std::vector<int> vec{ 6,5,9 };
    std::list<int> list_4(vec.begin(), vec.end());
    //遍历方式
    for (const auto& li: list_4) {
        std::cout << li << " ";
    }
    std::cout << std::endl;
    list_4.insert(list_4.begin(), 5);
    for (std::list<int>::iterator it = list_4.begin(); it != list_4.end();it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::list<int> list_5{ 9,3,8 };
    list_4.splice(list_4.begin(), list_5,list_5.begin());
    list_4.remove(5);
    for (const auto& li : list_4) {
        std::cout << li << " ";
    }
    list_5.sort();
    list_5.unique();
    list_4.sort();
    list_4.merge(list_5);
    list_4.unique();
    for (const auto& li : list_4) {
        std::cout << li << " ";
    }
}
```

### 标准STL关联容器

#### set

特点:  基于二叉树、元素唯一且按键有序

适用场景: 快速查找、按序便利、自动去重

时间复杂度: 插入 O(log n)  删除  O(log n)  查找 find/count O(log n) 

常用方法:

```C++
void setExample() {
    //set构造方式
    /*std::set的构造方式只接受三种:
    * 1、范围构造: 接受两个迭代器  如(begin()、end())
    * 2、初始化构造: 接收{...}包裹的内容
    * 3、复制\移动构造: 接受另一个 std::set
    */
    std::set<std::string> set;//默认构造方式
    std::string s = "Hello";
    std::set<char> set1(s.begin(), s.end());
    for (const auto& s:set1) {
        std::cout << s << ",";
    }
    std::cout << std::endl;
    std::vector<std::string> vec;
    vec.reserve(10);
    int number[] = { 0,1,2,3,4,5,6,7,8,9 };
    std::string word = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
    //随机数生成
    std::random_device rd;
    std::mt19937 gen(rd());//梅森旋转算法作为随机数引擎
    std::uniform_int_distribution<int> dist(1,51);
    std::string code;
    for (int i = 0; i < 5;++i) {
        for (int j = 0; j < 5;++j) {
            code += word.at(dist(gen));
        }
        vec.push_back(code);
        code.clear();
    }
    std::set<std::string> codeSet(vec.begin(), vec.end());
    for (const auto& s: codeSet) {
        std::cout << s << ",";
    }
    std::cout << std::endl;
    auto it=codeSet.lower_bound("hello");
    if (it==codeSet.end()) {
        std::cout << "不存在" << std::endl;
    }
    std::cout << "it=" << *it << std::endl;
}
```

#### multiset

特点：与set类似、但是允许有相同元素

#### map

特点: 有序映射、按照键值对进行存放(key-value)、底层同样是平衡二叉树

#### multimap

