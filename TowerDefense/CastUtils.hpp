#pragma once
#ifndef CAST_UTILS_HPP
#define CAST_UTILS_HPP
//
/**
 * \brief 
 * http://www.ficksworkshop.com/blog/post/how-to-static-cast-std-unique-ptr
 * upcasting
 * \tparam D 
 * \tparam B 
 * \param base 
 * \return 
 */
template<typename D, typename B>
std::unique_ptr<D> static_cast_ptr(std::unique_ptr<B>& base)
{
    return std::unique_ptr<D>(static_cast<D*>(base.release()));
}

/**
 * \brief 
 * http://www.ficksworkshop.com/blog/post/how-to-static-cast-std-unique-ptr
 * upcasting
 * \tparam D 
 * \tparam B 
 * \param base 
 * \return 
 */
template<typename D, typename B>
std::unique_ptr<D> static_cast_ptr(std::unique_ptr<B>&& base)
{
    return std::unique_ptr<D>(static_cast<D*>(base.release()));
}

/** 
 * \brief 
 * https://stackoverflow.com/questions/21174593/downcasting-unique-ptrbase-to-unique-ptrderived#21174979
 * downcasting
 * \tparam Derived 
 * \tparam Base 
 * \tparam Del 
 * \param p 
 * \return 
 */
template<typename Derived, typename Base, typename Del>
std::unique_ptr<Derived, Del> 
static_unique_ptr_cast( std::unique_ptr<Base, Del>&& p )
{
    auto d = static_cast<Derived *>(p.release());
    return std::unique_ptr<Derived, Del>(d, std::move(p.get_deleter()));
}

/** 
 * \brief 
 * https://stackoverflow.com/questions/21174593/downcasting-unique-ptrbase-to-unique-ptrderived#21174979
 * downcasting
 * \tparam Derived 
 * \tparam Base 
 * \tparam Del 
 * \param p 
 * \return 
 */
template<typename Derived, typename Base, typename Del>
std::unique_ptr<Derived, Del> 
dynamic_unique_ptr_cast( std::unique_ptr<Base, Del>&& p )
{
    if(Derived *result = dynamic_cast<Derived *>(p.get())) {
        p.release();
        return std::unique_ptr<Derived, Del>(result, std::move(p.get_deleter()));
    }
    return std::unique_ptr<Derived, Del>(nullptr, p.get_deleter());
}
#endif
