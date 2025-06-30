#ifdef __cplusplus
#import "react-native-crosssqlite.h" // Your C++ logic
#endif

#import <Crosssqlite/RNCrosssqliteSpec.h> // Auto-generated TurboModule interface

@interface Crosssqlite : NSObject <NativeCrosssqliteSpec>
- (NSString *)getJournalMode;
- (NSString *)select:(NSString *)sql;
@end
