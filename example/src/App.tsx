import { useState } from 'react';
import {
  SafeAreaView,
  Text,
  TextInput,
  Button,
  View,
  ScrollView,
  StyleSheet,
  Platform,
} from 'react-native';
import * as RNFS from '@dr.pogodin/react-native-fs';
import * as Crosssqlite from 'react-native-crosssqlite';

const App = () => {
  const [input, setInput] = useState('');
  const [status, setStatus] = useState('Ready');
  const [dbOpen, setDbOpen] = useState(false);

  const getDatabasePath = (): string => {
    if (Platform.OS === 'ios') {
      return `${RNFS.DocumentDirectoryPath}/test.db`;
    } else if (Platform.OS === 'android') {
      return `${RNFS.ExternalDirectoryPath}/test.db`;
    } else {
      // For Windows or fallback
      return 'test.db';
    }
  };

  const openDb = () => {
    try {
      const path = getDatabasePath();
      Crosssqlite.open(path);
      Crosssqlite.exec(
        `CREATE TABLE IF NOT EXISTS items (id INTEGER PRIMARY KEY AUTOINCREMENT, value TEXT);`
      );
      setDbOpen(true);
      setStatus('DB opened and table created.');
    } catch (e) {
      setStatus(`Open failed: ${e}`);
    }
  };

  const insertData = () => {
    if (!input) return;
    try {
      Crosssqlite.exec(`INSERT INTO items (value) VALUES ('${input}');`);
      setStatus(`Inserted: ${input}`);
      setInput('');
    } catch (e) {
      setStatus(`Insert failed: ${e}`);
    }
  };

  const selectAll = () => {
    try {
      const result = Crosssqlite.select('SELECT * FROM items;');
      setStatus('Rows: ' + result);
    } catch (e) {
      setStatus('Select failed: ' + e);
    }
  };

  const checkWAL = () => {
    try {
      const mode = Crosssqlite.getJournalMode();
      setStatus('Journal mode: ' + mode);
    } catch (e) {
      setStatus('getJournalMode failed: ' + e);
    }
  };

  const testMultiply = () => {
    const result = Crosssqlite.multiply(6, 9);
    setStatus(`6 x 9 = ${result}`);
  };

  const closeDb = () => {
    try {
      Crosssqlite.close();
      setDbOpen(false);
      setStatus('Database closed.');
    } catch (e) {
      setStatus('Close failed: ' + e);
    }
  };

  return (
    <SafeAreaView style={styles.container}>
      <ScrollView>
        <Text style={styles.header}>CrossSQLite Example</Text>

        <View style={styles.row}>
          <Button title="📂 Open DB" onPress={openDb} disabled={dbOpen} />
          <Button title="❌ Close DB" onPress={closeDb} disabled={!dbOpen} />
        </View>

        <TextInput
          style={styles.input}
          placeholder="Enter a value"
          value={input}
          onChangeText={setInput}
        />

        <Button title="Insert" onPress={insertData} disabled={!dbOpen} />
        <Button title="Select All" onPress={selectAll} disabled={!dbOpen} />
        <Button title="Check WAL Mode" onPress={checkWAL} disabled={!dbOpen} />
        <Button title="Multiply 6 × 9" onPress={testMultiply} />

        <Text style={styles.status}>Status: {status}</Text>
      </ScrollView>
    </SafeAreaView>
  );
};

const styles = StyleSheet.create({
  container: { flex: 1, padding: 16 },
  header: {
    fontSize: 22,
    fontWeight: 'bold',
    marginBottom: 20,
    textAlign: 'center',
  },
  row: {
    flexDirection: 'row',
    justifyContent: 'space-between',
    marginBottom: 20,
  },
  input: {
    borderWidth: 1,
    borderColor: '#ccc',
    padding: 10,
    borderRadius: 5,
    marginBottom: 12,
  },
  status: {
    marginTop: 20,
    fontSize: 16,
    fontStyle: 'italic',
  },
});

export default App;
