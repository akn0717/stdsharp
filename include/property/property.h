﻿// Created by BlurringShadow at 2021-03-11-下午 4:30

#pragma once

#include "reflection/reflection.h"
#include "setter.h"
#include "getter.h"

namespace stdsharp::property
{
    template<::std::invocable GetterT, settable<getter_value_t<GetterT>> SetterT>
    class property_member
    {
    public:
        using getter_t = GetterT;
        using setter_t = SetterT;

        using value_type = getter_value_t<GetterT>;
        using reference = value_type&;
        using const_reference = const value_type&;

        template<typename Getter, typename Setter>
            requires ::std::constructible_from<GetterT, Getter> &&
                ::std::constructible_from<SetterT, Setter>
        constexpr property_member(Getter&& g, Setter&& s) //
            noexcept(concepts::nothrow_constructible_from<GetterT, Getter>&& //
                         concepts::nothrow_constructible_from<SetterT, Setter>):
            getter_(::std::forward<Getter>(g)), setter_(::std::forward<Setter>(s))
        {
        }

        template<typename... Args>
            requires ::std::invocable<setter_t, Args...>
        constexpr decltype(auto) set(Args&&... args) //
            noexcept(concepts::nothrow_invocable<setter_t, Args...>)
        {
            return setter_(::std::forward<Args>(args)...);
        };

        template<auto Name>
            // TODO MSVC ICE WORKAROUND
            requires(type_traits::invoke_result<functional::equal_to_v, Name, "set"_ltr>)
        constexpr auto operator()(const reflection::member_t<Name>) noexcept
        {
            return functional::make_invocable_ref(setter_);
        }

        constexpr const_reference get() const //
            noexcept(concepts::nothrow_invocable<getter_t>)
        {
            return getter_(); //
        };

        template<auto Name>
            // TODO MSVC ICE WORKAROUND
            requires(type_traits::invoke_result<functional::equal_to_v, Name, "get"_ltr>)
        constexpr auto operator()(const reflection::member_t<Name>) const noexcept
        {
            return functional::make_invocable_ref(functional::nodiscard_tag, getter_);
        }

        template<typename T>
            requires ::std::invocable<setter_t, T>
        constexpr auto& operator=(T&& t) //
            noexcept(concepts::nothrow_invocable<setter_t, T>)
        {
            setter_(::std::forward<T>(t));
            return *this;
        }

        constexpr const_reference operator()() const noexcept(noexcept(get())) { return get(); }

        template<typename OtherGetter, typename OtherSetter>
            requires concepts::
                weakly_equality_comparable_with<value_type, getter_value_t<OtherGetter>>
        constexpr bool operator==(const property_member<OtherGetter, OtherSetter>& other //
        ) const noexcept(noexcept((*this)() == other()))
        {
            return (*this)() == other();
        }

        template<typename OtherGetter, typename OtherSetter>
            requires concepts::partial_ordered_with<value_type, getter_value_t<OtherGetter>>
        constexpr auto operator<=>(const property_member<OtherGetter, OtherSetter>& other //
        ) const noexcept(noexcept((*this)() <=> other()))
        {
            return (*this)() <=> other();
        }

        template<typename T>
            requires concepts::weakly_equality_comparable_with<value_type, T>
        constexpr bool operator==(const T& other) const noexcept(noexcept((*this)() == other))
        {
            return (*this)() == other;
        }

        template<typename T>
            requires concepts::partial_ordered_with<value_type, T>
        constexpr auto operator<=>(const T& other) const noexcept(noexcept((*this)() <=> other))
        {
            return (*this)() <=> other;
        }

        template<typename T>
            requires concepts::weakly_equality_comparable_with<T, value_type>
        friend constexpr bool operator==(const T& other, const property_member& instance) //
            noexcept(noexcept(other == instance()))
        {
            return other == instance();
        }

        template<typename T>
            requires concepts::partial_ordered_with<T, value_type>
        friend constexpr auto operator<=>(const T& other, const property_member& instance) //
            noexcept(noexcept(other <=> instance()))
        {
            return other <=> instance();
        }

    private:
        getter_t getter_;
        setter_t setter_;
    };

    template<typename T, typename U>
    property_member(T&&, U&&) -> property_member<T, U>;
}
