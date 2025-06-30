#import "Crosssqlite.h"
#import "sqlite_bridge.h"
#import "react-native-crosssqlite.h"

@implementation Crosssqlite
RCT_EXPORT_MODULE()

- (NSNumber *)multiply:(double)a b:(double)b {
  return @(crosssqlite::multiply(a, b));
}

- (NSNumber *)open:(NSString *)path {
  int rc = open_db([path UTF8String]);
  return @(rc);
}

- (NSNumber *)exec:(NSString *)sql {
  int rc = exec_sql([sql UTF8String]);
  return @(rc);
}

- (void)close {
  close_db();
}

- (NSString *)getJournalMode {
  const char* mode = get_journal_mode();
  return [NSString stringWithUTF8String:mode];
}

- (NSString *)select:(NSString *)sql {
  const char* result = select_json([sql UTF8String]);
  return [NSString stringWithUTF8String:result];
}

- (std::shared_ptr<facebook::react::TurboModule>)getTurboModule:
(const facebook::react::ObjCTurboModule::InitParams &)params {
  return std::make_shared<facebook::react::NativeCrosssqliteSpecJSI>(params);
}

@end
