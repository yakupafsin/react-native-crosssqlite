# react-native-crosssqlite

🗄️ **Cross-Platform SQLite for React Native** - A high-performance SQLite Turbo Module that works seamlessly across iOS, Android, and Windows platforms.

## ✨ Features

- 🚀 **High Performance**: Built as a React Native Turbo Module with C++ core
- 🌍 **Cross-Platform**: Supports iOS, Android, and Windows
- 📱 **Native SQLite**: Uses native SQLite3 library on each platform
- 🔄 **WAL Mode**: Optimized with Write-Ahead Logging for better performance
- 📊 **JSON Results**: SELECT queries return results in JSON format
- 🛡️ **Type Safe**: Full TypeScript support with proper type definitions

## 📦 Installation

```sh
npm install react-native-crosssqlite
```

### Platform Setup

#### iOS
No additional setup required. The module will be automatically linked.

#### Android
No additional setup required. The module will be automatically linked.

#### Windows
1. Install React Native Windows CLI:
   ```sh
   npm install -g @react-native-windows/cli
   ```
2. Initialize Windows support in your project:
   ```sh
   npx @react-native-windows/cli@latest init --overwrite
   ```

## 🚀 Usage

### Basic Example

```typescript
import * as SQLite from 'react-native-crosssqlite';

// Open a database
const result = SQLite.open('/path/to/database.db');
if (result === 0) {
  console.log('Database opened successfully');
}

// Create a table
SQLite.exec(`
  CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    email TEXT UNIQUE
  );
`);

// Insert data
SQLite.exec(`
  INSERT INTO users (name, email)
  VALUES ('John Doe', 'john@example.com');
`);

// Query data
const users = SQLite.select('SELECT * FROM users;');
console.log('Users:', JSON.parse(users));

// Check journal mode (should be 'wal')
const journalMode = SQLite.getJournalMode();
console.log('Journal mode:', journalMode);

// Close database
SQLite.close();
```

### Platform-Specific Database Paths

```typescript
import { Platform } from 'react-native';
import RNFS from '@dr.pogodin/react-native-fs';

const getDatabasePath = (): string => {
  if (Platform.OS === 'ios') {
    return `${RNFS.DocumentDirectoryPath}/myapp.db`;
  } else if (Platform.OS === 'android') {
    return `${RNFS.ExternalDirectoryPath}/myapp.db`;
  } else if (Platform.OS === 'windows') {
    return 'myapp.db'; // Relative to app directory
  }
  return 'myapp.db';
};

SQLite.open(getDatabasePath());
```

## 📚 API Reference

### `open(path: string): number`
Opens a SQLite database at the specified path.
- **Returns**: `0` on success, error code on failure
- **Note**: Automatically enables WAL mode for better performance

### `exec(sql: string): number`
Executes a SQL statement (INSERT, UPDATE, DELETE, CREATE, etc.).
- **Returns**: `0` on success, error code on failure

### `select(sql: string): string`
Executes a SELECT query and returns results as JSON.
- **Returns**: JSON string array of result rows

### `close(): void`
Closes the currently open database.

### `getJournalMode(): string`
Returns the current journal mode of the database.
- **Returns**: Journal mode string (typically "wal")

### `multiply(a: number, b: number): number`
Utility function for testing the module.
- **Returns**: Product of two numbers

## 🏗️ Architecture

This module uses a shared C++ core with platform-specific bindings:

```
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│   iOS (Obj-C)   │    │ Android (JNI)   │    │ Windows (WinRT) │
└─────────┬───────┘    └─────────┬───────┘    └─────────┬───────┘
          │                      │                      │
          └──────────────────────┼──────────────────────┘
                                 │
                    ┌─────────────▼─────────────┐
                    │     C++ SQLite Bridge     │
                    │   (sqlite_bridge.cpp)     │
                    └─────────────┬─────────────┘
                                  │
                    ┌─────────────▼─────────────┐
                    │      SQLite3 Library      │
                    │      (sqlite3.c)          │
                    └───────────────────────────┘
```

## 🧪 Example App

Check out the example app in the `example/` directory to see the module in action:

```sh
cd example
npm install

# For iOS
npx react-native run-ios

# For Android
npx react-native run-android

# For Windows (after setup)
npx react-native run-windows
```

## 🤝 Contributing

See the [contributing guide](CONTRIBUTING.md) to learn how to contribute to the repository and the development workflow.

## 📄 License

MIT

---

Made with [create-react-native-library](https://github.com/callstack/react-native-builder-bob)
