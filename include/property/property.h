﻿// Created by BlurringShadow at 2021-03-11-下午 4:30

#pragma once

#include "type_traits/object.h"
#include "setter.h"
#include "getter.h"

namespace stdsharp::property
{
    template<
        ::std::invocable GetterT,
        ::stdsharp::property::settable<::stdsharp::property::getter_value_t<GetterT>> SetterT
        // clang-format off
    > // clang-format on
    class property_member
    {
    public:
        using getter_t = GetterT;
        using setter_t = SetterT;

        using value_type = ::stdsharp::property::getter_value_t<GetterT>;
        using reference = value_type&;
        using const_reference = const value_type&;

        static constexpr ::std::type_identity<setter_t> set_tag{};
        static constexpr ::std::type_identity<getter_t> get_tag{};

        template<typename Getter, typename Setter>
            requires requires
            {
                requires ::std::constructible_from<GetterT, Getter> &&
                    ::std::constructible_from<SetterT, Setter>;
            }
        property_member(Getter&& g, Setter&& s) //
            noexcept(::stdsharp::concepts::nothrow_constructible_from<GetterT, Getter>&& //
                     ::stdsharp::concepts::nothrow_constructible_from<SetterT, Setter>):
            getter_(::std::forward<Getter>(g)), setter_(::std::forward<Setter>(s))
        {
        }

        constexpr auto operator()(const decltype(set_tag)) noexcept
        {
            return ::stdsharp::functional::make_invocable_ref(setter_);
        }

        constexpr auto operator()(const decltype(get_tag)) const noexcept
        {
            return ::stdsharp::functional:: //
                make_invocable_ref(::stdsharp::functional::nodiscard_tag, getter_);
        }

        template<typename... Args>
            requires ::std::invocable<setter_t, Args...>
        constexpr decltype(auto) set(Args&&... args) //
            noexcept(::stdsharp::concepts::nothrow_invocable<setter_t, Args...>)
        {
            return setter_(::std::forward<Args>(args)...);
        };

        constexpr const_reference get() const //
            noexcept(::stdsharp::concepts::nothrow_invocable<getter_t>)
        {
            return getter_(); //
        };

        template<typename T>
            requires ::std::invocable<setter_t, T>
        constexpr auto& operator=(T&& t) //
            noexcept(::stdsharp::concepts::nothrow_invocable<setter_t, T>)
        {
            setter_(std::forward<T>(t));
            return *this;
        }

        constexpr const_reference operator()() const noexcept(noexcept(get())) { return get(); }

    private:
        getter_t getter_;
        setter_t setter_;
    };

    template<typename T, typename U>
    property_member(T&&, U&&) -> property_member<T, U>;
}
