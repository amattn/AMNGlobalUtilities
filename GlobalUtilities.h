/******************************************************************************
 *  \file GlobalUtilities.h
 *  \author Matt Nunogawa (@amattn)
 *
 *  \brief Useful, Nigh-Indispensable Collection of macros and utilities
 *  \details Original version created by Matthew Nunogawa on Mon Sep 22 2003.
 *           https://github.com/amattn/AMNGlobalUtilities
 *
 *  \version 2.1.8
 *  \copyright Copyright Matthew Nunogawa 2003-2013.
 *             This software is provided under the MIT License.
 *             Please see LICENSE file.
 */

#pragma mark -
#pragma mark ** Convenience macros **

// Quickly make an NSError
#define AMN_QUICK_ERROR(error_code, error_description) [NSError errorWithDomain:NSStringFromClass([self class]) code:error_code userInfo:[NSDictionary dictionaryWithObject:error_description forKey:NSLocalizedDescriptionKey]];

// Quickly get portrait mode
#define AMN_ORIENTATION_IS_PORTRAIT UIInterfaceOrientationIsPortrait([[UIApplication sharedApplication] statusBarOrientation])

#pragma mark -
#pragma mark ** Log macros **

// standard types
#define LOG_BOOL(object)    (NSLog(@"" #object @" %@", (object ? @"YES" : @"NO") ));
#define LOG_CHAR(object)    (NSLog(@"" #object @" %c", object ));
#define LOG_INT32(object)   (NSLog(@"" #object @" %d", object ));
#define LOG_UINT32(object)  (NSLog(@"" #object @" %u", object ));
#define LOG_LONG(object)    (NSLog(@"" #object @" %ld", object ));
#define LOG_ULONG(object)   (NSLog(@"" #object @" %lu", object ));
#define LOG_INT64(object)   (NSLog(@"" #object @" %qi", object ));
#define LOG_UINT64(object)  (NSLog(@"" #object @" %qu", object ));
#define LOG_FLOAT(object)   (NSLog(@"" #object @" %f",object ));
#define LOG_DOUBLE(object)  (NSLog(@"" #object @" %lf",object ));

// NSInteger and NSInteger are platform independant integer types
#if __LP64__ || (TARGET_OS_EMBEDDED && !TARGET_OS_IPHONE) || TARGET_OS_WIN32 || NS_BUILD_32_LIKE_64
#define LOG_INTEGER(object)     (NSLog(@"" #object @" %ld", object ));
#define LOG_UINTEGER(object)    (NSLog(@"" #object @" %lu", object ));
#else
#define LOG_INTEGER(object)     (NSLog(@"" #object @" %d", object ));
#define LOG_UINTEGER(object)    (NSLog(@"" #object @" %u", object ));
#endif

// Various Cocoa/Objective-C log macros
#define LOG_OBJECT(object)  (NSLog(@"" #object @" %@ %@:%d", [object description], [[NSString stringWithUTF8String:__FILE__] lastPathComponent], __LINE__));
#define LOG_KIND_OF_CLASS(object)  (NSLog(@"[" #object @" class] %@", NSStringFromClass([object class])));
#define LOG_METHOD          (NSLog(@"%@ %@:%d\n%@", NSStringFromSelector(_cmd), [[NSString stringWithUTF8String:__FILE__] lastPathComponent], __LINE__, self))
#define LOG_END_METHOD      (NSLog(@"END %@", NSStringFromSelector(_cmd)))
#define LOG_METHOD_NAME     (NSLog(@"%p %@ %@", self, NSStringFromClass([self class]), NSStringFromSelector(_cmd)))
#define LOG_METHOD_THREAD   (NSLog(@"%@ %@ %@:%d\n%@", NSStringFromSelector(_cmd), [NSThread currentThread], [[NSString stringWithUTF8String:__FILE__] lastPathComponent], __LINE__, self))
#define LOG_CLASS_METHOD    (NSLog(@"%@ %@", NSStringFromClass([self class]), NSStringFromSelector(_cmd)))

// Profiling Macros
#define START_TIME(tag) NSDate *startTime_ ## tag = [NSDate date];NSLog(@"start           " #tag);
#define CHECK_TIME(tag) NSLog(@"elapsed %0.5f " #tag, [[NSDate date] timeIntervalSinceDate:startTime_ ## tag]);

// Various Cocoa struct log macros
// NSRange
#define LOG_RANGE(range)    (NSLog(@"" #range @" loc:%u len:%u", range.location, range.length ));
// CGPoint
#define LOG_POINT(point)    (NSLog(@"" #point @" x:%f y:%f", point.x, point.y ));
// CGSize
#define LOG_SIZE(size)      (NSLog(@"" #size @" width:%f height:%f", size.width, size.height ));
// CGRect
#define LOG_RECT(rect)      (NSLog(@"" #rect @" x:%f y:%f w:%f h:%f", rect.origin.x, rect.origin.y, rect.size.width, rect.size.height ));
// CLLocationCoordinate2D
#define LOG_COORD2D(coord)  (NSLog(@"" #coord @" lat,lon: %+.6f,%+.6f",coord.latitude, coord.longitude ));

#pragma mark -
#pragma mark ** Assertion macros **

// Standard Assertions
#define ASSERT_NIL(x)           NSAssert4((x == nil), @"\n\n    ****  Unexpected Nil Assertion  ****\n    ****  Expected nil, but " #x @" is not nil.\nin file:%s at line %i in Method %@ with object:\n %@", __FILE__, __LINE__, NSStringFromSelector(_cmd), self)
#define ASSERT_NOT_NIL(x)       NSAssert4((x != nil), @"\n\n    ****  Unexpected Nil Assertion  ****\n    ****  Expected not nil, " #x @" is nil.\nin file:%s at line %i in Method %@ with object:\n %@", __FILE__, __LINE__, NSStringFromSelector(_cmd), self)
#define ASSERT_ALWAYS           NSAssert4(FALSE, @"\n\n    ****  Unexpected Assertion  **** \nAssertion in file:%s at line %i in Method %@ with object:\n %@", __FILE__, __LINE__, NSStringFromSelector(_cmd), self)
#define ASSERT_TRUE(test)       NSAssert4(test, @"\n\n    ****  Unexpected Assertion  **** \nAssertion in file:%s at line %i in Method %@ with object:\n %@", __FILE__, __LINE__, NSStringFromSelector(_cmd), self)
#define ASSERT_FALSE(test)      NSAssert4(!test, @"\n\n    ****  Unexpected Assertion  **** \nAssertion in file:%s at line %i in Method %@ with object:\n %@", __FILE__, __LINE__, NSStringFromSelector(_cmd), self)
#define ASSERT_WITH_MESSAGE(x)                  NSAssert5(FALSE, @"\n\n    ****  Unexpected Assertion  **** \nReason: %@\nAssertion in file:%s at line %i in Method %@ with object:\n %@", x, __FILE__, __LINE__, NSStringFromSelector(_cmd), self)
#define ASSERT_TRUE_WITH_MESSAGE(test, msg)     NSAssert5(test, @"\n\n    ****  Unexpected Assertion  **** \nReason: %@\nAssertion in file:%s at line %i in Method %@ with object:\n %@", msg, __FILE__, __LINE__, NSStringFromSelector(_cmd), self)
#define ASSERT_FALSE_WITH_MESSAGE(test, msg)    NSAssert5(!test, @"\n\n    ****  Unexpected Assertion  **** \nReason: %@\nAssertion in file:%s at line %i in Method %@ with object:\n %@", msg, __FILE__, __LINE__, NSStringFromSelector(_cmd), self)

// Useful, protective assertion macros
#define ASSERT_IS_CLASS(x, class)    NSAssert5([x isKindOfClass:class], @"\n\n    ****  Unexpected Class Assertion  **** \nReason: Expected class:%@ but got:%@\nAssertion in file:%s at line %i in Method %@\n\n", NSStringFromClass(class), x, __FILE__, __LINE__, NSStringFromSelector(_cmd))
#define SUBCLASSES_MUST_OVERRIDE     NSAssert2(FALSE, @"%@ Subclasses MUST override this method:%@\n\n", NSStringFromClass([self class]), NSStringFromSelector(_cmd));
#define SHOULD_NEVER_GET_HERE        NSAssert4(FALSE, @"\n\n    ****  Should Never Get Here  **** \nAssertion in file:%s at line %i in Method %@ with object:\n %@\n\n", __FILE__, __LINE__, NSStringFromSelector(_cmd), self)

// Blocks assertion, prevents NSAssert retain cycles in blocks
// http://getitdownonpaper.com/journal/2011/9/27/making-nsassert-play-nice-with-blocks.html
#if !defined(NS_BLOCK_ASSERTIONS)

#define BlockAssert(condition, desc, ...) \
do {\
if (!(condition)) { \
[[NSAssertionHandler currentHandler] handleFailureInFunction:NSStringFromSelector(_cmd) \
file:[NSString stringWithUTF8String:__FILE__] \
lineNumber:__LINE__ \
description:(desc), ##__VA_ARGS__]; \
}\
} while(0);

#else // NS_BLOCK_ASSERTIONS defined

#define BlockAssert(condition, desc, ...) 

#endif

#pragma mark -
#pragma mark ** Utilities **

// Unabashedly cribbed from Wil Shipley (of Delicious Monster fame)
// http://www.wilshipley.com/blog/2005/10/pimp-my-code-interlude-free-code.html
static inline BOOL isEmpty(id thing)
{
    return thing == nil
    || ([thing respondsToSelector:@selector(length)] && [(NSData *)thing length] == 0)
    || ([thing respondsToSelector:@selector(count)] && [(NSArray *)thing count] == 0);
}

// UUIDs are uuuseful.
static inline CFStringRef createUniqueString(void)
{
    CFUUIDRef uuid = CFUUIDCreate(NULL);
    CFStringRef uuidStringRef = CFUUIDCreateString(NULL, uuid);
    CFRelease(uuid);
    return uuidStringRef;
}
