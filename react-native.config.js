/**
 * @type {import('@react-native-community/cli-types').UserDependencyConfig}
 */
module.exports = {
  dependency: {
    platforms: {
      android: {
        cmakeListsPath: 'generated/jni/CMakeLists.txt',
      },
      windows: {
        sourceDir: 'windows',
        solutionFile: 'Crosssqlite.sln',
        projects: [
          {
            projectFile: 'Crosssqlite/Crosssqlite.vcxproj',
            directDependency: true,
          },
        ],
      },
    },
  },
};
