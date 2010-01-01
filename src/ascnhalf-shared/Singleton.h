/* AscNHalf */

#ifndef WOWSERVER_SINGLETON_H
#define WOWSERVER_SINGLETON_H

#include "Errors.h"

template < class type > class SERVER_DECL Singleton {
public:
  /// Constructor
  Singleton( ) {
	/// If you hit this assert, this singleton already exists -- you can't create another one!
	WPAssert( mSingleton == 0 );
	mSingleton = static_cast<type *>(this);
  }
  /// Destructor
  virtual ~Singleton( ) {
	mSingleton = 0;
  }

#ifdef WIN32
	INLINE static type & getSingleton( ) { WPAssert( mSingleton ); return *mSingleton; }
	INLINE static type * getSingletonPtr( ) { return mSingleton; }
#else
	INLINE static type & getSingleton( ) { WPAssert( mSingleton ); return *mSingleton; }
	INLINE static type * getSingletonPtr( ) { return mSingleton; }
#endif

protected:

  /// Singleton pointer, must be set to 0 prior to creating the object
  static type * mSingleton;
};

/// Should be placed in the appropriate .cpp file somewhere
#define initialiseSingleton( type ) \
	template <> type * Singleton < type > :: mSingleton = 0

/// To be used as a replacement for initialiseSingleton( )
///  Creates a file-scoped Singleton object, to be retrieved with getSingleton
#define createFileSingleton( type ) \
	initialiseSingleton( type ); \
	type the##type

#endif

