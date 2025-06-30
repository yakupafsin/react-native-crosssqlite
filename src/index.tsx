import Crosssqlite from './NativeCrosssqlite';

export function multiply(a: number, b: number): number {
  return Crosssqlite.multiply(a, b);
}

export function open(path: string): number {
  return Crosssqlite.open(path);
}

export function exec(sql: string): number {
  return Crosssqlite.exec(sql);
}

export function close(): void {
  return Crosssqlite.close();
}

export function select(sql: string): string {
  return Crosssqlite.select(sql);
}

export function getJournalMode(): string {
  return Crosssqlite.getJournalMode();
}
