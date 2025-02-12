#ifndef BC_BASE_H
#define BC_BASE_H


#include <iostream>
#include <vector>
#include <functional>
#include <map>
#include <string>




// ******************  cout  *************************
// @ name: cout
// @ func:
// @ para:
// ***************************************************

// 检查
template<typename T, typename = void>
constexpr bool has_stream_operator = false;

template<typename T>
constexpr bool has_stream_operator<T, std::void_t<decltype(std::cout << std::declval<T>())>> = true;

template <typename>
constexpr bool _cout_is_vector = false;

template <typename Args>
constexpr bool _cout_is_vector<std::vector<Args>> = true;

// 打印值
template<typename T>
inline void _printval(T val)
{
    if constexpr (has_stream_operator<T>)
    {
        std::cout << val << " ";
    }
    else if constexpr (_cout_is_vector<T>)
    {
        for (auto& cur : val)
            _printval(cur);
        std::cout << std::endl;
    }
    else
    {
        static_assert(has_stream_operator<T>, "no << operator");
    }
}

template<typename ... Arg>
inline void cccout(Arg const & ...args)
{
    (_printval(args), ...);
    std::cout << std::endl;
}


#define coutfileline(str)  cccout(str, __FILE__, __LINE__, __func__);







// ******************  初始化  ************************
// @ name: Init
// @ func:
// @ para:
// ***************************************************

// 单例初始化基类
class SingletonInitBase
{
protected:
    // 初始化函数
    virtual void Init() = 0;

public:
    // 更新函数
    virtual void Update() {}

public:
    static void InitMap()
    {
        for (auto cur : SingletonInitBase::init_map)
        {
            std::string str = "初始化 id:" + std::to_string(cur.first) + ", name: " + name_map[cur.second];
            cccout(str);
            cur.second->Init();
        }
    }

protected:
    inline static std::multimap<int, SingletonInitBase*> init_map;
    inline static std::map<SingletonInitBase*, std::string> name_map;
};


template<typename T>
class SingletonInit : public SingletonInitBase
{
public:
    static T* ptr();

protected:
    SingletonInit() = default;
    SingletonInit(const SingletonInit&) = delete;
    SingletonInit& operator=(const SingletonInit&) = delete;

protected:
    static T m_obj;  // 单例对象
};

template <typename T>
T SingletonInit<T>::m_obj;

template<typename T>
T* SingletonInit<T>::ptr()
{
    return &m_obj;
}



// 全局初始化
#define SINGLETON_INIT(Name)                                     \
    private:                                                     \
    friend class SingletonInit<Name>;                            \
    Name() {                                                     \
        std::string str = std::string("Init ") + #Name;          \
	    cccout(str);                                             \
        m_obj.Init();                                            \
    }                                                            

// 顺序初始化                                                     
#define SINGLETON_INIT_IDX(Name, i)                              \
    private:                                                     \
    friend class SingletonInit<Name>;                            \
    Name() {                                                     \
        name_map[&m_obj] = #Name;                                \
        init_map.emplace((int)i, (SingletonInitBase*)&m_obj);    \
    }                                                            






#endif