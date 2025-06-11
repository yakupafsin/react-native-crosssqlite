import Crosssqlite from './NativeCrosssqlite';

export function multiply(a: number, b: number): number {
  return Crosssqlite.multiply(a, b);
}
