#ifndef COM_MASAERS_FUNTUPLE_HPP
#define COM_MASAERS_FUNTUPLE_HPP
#include <tuple>
#include <functional>
#include <utility>
#include <type_traits>

namespace com { namespace masaers { namespace funtuple {
	namespace detail {
		template<int I, typename Tuple> struct in_tuple : std::integral_constant<bool, 0 <= I && I < std::tuple_size<typename std::decay<Tuple>::type>::value> {};

		template<int At, int Step, typename FunTuple, typename Result>
		inline constexpr Result apply_chain_helper(std::false_type, FunTuple&& funtuple, Result&& result) {
			return std::forward<Result>(result);
		}
		template<int At, int Step,typename FunTuple, typename Result>
		inline constexpr decltype(auto) apply_chain_helper(std::true_type, FunTuple&& funtuple, Result&& result) {
			return apply_chain_helper<At+Step, Step>(in_tuple<At+Step, FunTuple>(),
				                                       std::forward<FunTuple>(funtuple),
				                                       std::get<At>(funtuple)(std::forward<Result>(result)));
		}
	  template<int Start, int Step, typename FunTuple, typename... Args>
    inline constexpr decltype(auto) apply_chain(FunTuple&& funtuple, Args&&... args) {
      return apply_chain_helper<Start+Step, Step>(in_tuple<Start+Step, FunTuple>(),
                                                  std::forward<FunTuple>(funtuple),
                                                  std::get<Start>(funtuple)(std::forward<Args>(args)...));
    }

	} // namespace detail
	template<typename FunTuple, typename... Args>
	inline constexpr decltype(auto) apply_pipe(FunTuple&& funtuple, Args&&... args) {
		return detail::apply_chain<0, 1>(std::forward<FunTuple>(funtuple), std::forward<Args>(args)...);
	}
	template<typename FunTuple, typename... Args>
	inline constexpr decltype(auto) apply_compose(FunTuple&& funtuple, Args&&... args) {
		return detail::apply_chain<std::tuple_size<typename std::decay<FunTuple>::type>::value-1, -1>(std::forward<FunTuple>(funtuple), std::forward<Args>(args)...);
	}
}}} // namespace com::masaers::funtuple


#endif
