#ifndef MUSIC_MISC_HH
#if MUSIC_USE_MPI
#include "music/error.hh"
#include <type_traits>
#include <iostream>
#include <map>
#include <vector>
#include <memory>

namespace MUSIC
{

	template<typename T>
	std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream, const T& e)
	{
			return stream << static_cast<typename std::underlying_type<T>::type>(e);
	}

	template<typename T>
	using SPVec = std::vector<std::shared_ptr<T>>;

	template<class AbstractProduct, typename IdentifierType, typename ProductCreator>
	class Factory
	{
		using ClsMap = std::map<IdentifierType, AbstractProduct>;

		public:

			bool Register (const IdentifierType& id, ProductCreator creator)
			{
				return cls_register_.insert (ClsMap::value_type (id, creator)).second;
			}

			bool Unregister (const IdentifierType& id)
			{
				return cls_register_.erase (id) == 1;
			}

			std::unique_ptr<AbstractProduct> CreateObject (const IdentifierType& id)
			{
				auto it = cls_register_.find (id);
				if (it != cls_register_.end ())
				{
					return (it->second) ();
				}
				error (std::string ("Factory could not find registered product for the given type-identifier"));
			}

		private:
			ClsMap cls_register_;
	};

}
#endif
#define MUSIC_MISC_HH
#endif
