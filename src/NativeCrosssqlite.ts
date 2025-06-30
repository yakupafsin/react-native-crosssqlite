import type { TurboModule } from 'react-native';
import { TurboModuleRegistry } from 'react-native';

export interface Spec extends TurboModule {
  multiply(a: number, b: number): number;
  open(path: string): number;
  exec(sql: string): number;
  close(): void;
  select(sql: string): string;
  getJournalMode(): string;
}

export default TurboModuleRegistry.getEnforcing<Spec>('Crosssqlite');
