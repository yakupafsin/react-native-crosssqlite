# 🚀 Release and Publishing Guide

This guide explains how to create releases and publish the `react-native-crosssqlite` package to npm using GitHub Actions.

## 📋 Prerequisites

### 1. NPM Account Setup
1. Create an account on [npmjs.com](https://www.npmjs.com/)
2. Generate an access token:
   - Go to [npm Access Tokens](https://www.npmjs.com/settings/tokens)
   - Click "Generate New Token"
   - Choose "Automation" type
   - Copy the token (starts with `npm_`)

### 2. GitHub Secrets Setup
Add the following secrets to your GitHub repository:

1. Go to your repository on GitHub
2. Navigate to **Settings** → **Secrets and variables** → **Actions**
3. Add these secrets:

| Secret Name | Description | Value |
|-------------|-------------|-------|
| `NPM_TOKEN` | NPM automation token | `npm_xxxxxxxxxxxxxxxx` |

**Note**: `GITHUB_TOKEN` is automatically provided by GitHub Actions.

## 🎯 Release Process

### Option 1: Manual Release (Recommended)

1. **Go to GitHub Actions**:
   - Navigate to your repository
   - Click on **Actions** tab
   - Select **Release and Publish** workflow

2. **Trigger Manual Release**:
   - Click **Run workflow**
   - Choose the release type:
     - `patch` - Bug fixes (1.0.0 → 1.0.1)
     - `minor` - New features (1.0.0 → 1.1.0)
     - `major` - Breaking changes (1.0.0 → 2.0.0)
     - `prerelease` - Pre-release version (1.0.0 → 1.0.1-0)

3. **What happens automatically**:
   - ✅ Runs all tests and linting
   - ✅ Builds the package
   - ✅ Updates version in `package.json`
   - ✅ Generates changelog
   - ✅ Creates Git tag
   - ✅ Creates GitHub release
   - ✅ Publishes to npm

### Option 2: Command Line Release

If you prefer to release locally:

```bash
# Install release-it globally (if not already installed)
npm install -g release-it

# Make sure you're on main branch and up to date
git checkout main
git pull origin main

# Run release (interactive)
npm run release

# Or specify version type directly
npx release-it patch   # Bug fixes
npx release-it minor   # New features  
npx release-it major   # Breaking changes
```

## 📦 Package Publishing

### Automatic Publishing
When you create a release using GitHub Actions, the package is automatically published to npm.

### Manual Publishing
If you need to publish manually:

```bash
# Build the package
npm run prepare

# Publish to npm
npm publish
```

## 🔍 Verification

After a successful release:

1. **Check GitHub**:
   - New tag should appear in **Releases**
   - Release notes should be generated

2. **Check npm**:
   - Visit: https://www.npmjs.com/package/react-native-crosssqlite
   - New version should be available

3. **Test Installation**:
   ```bash
   npm install react-native-crosssqlite@latest
   ```

## 📝 Release Notes

Release notes are automatically generated based on your commit messages. To get better release notes, use conventional commits:

```bash
feat: add Windows platform support
fix: resolve SQLite connection issue
docs: update README with Windows instructions
chore: update dependencies
```

## 🛠️ Troubleshooting

### NPM Token Issues
- Make sure the NPM_TOKEN secret is set correctly
- Verify the token has "Automation" permissions
- Check that the token hasn't expired

### Permission Issues
- Ensure you have publish permissions for the package
- For scoped packages, make sure the scope is configured correctly

### Build Failures
- Check that all tests pass locally
- Verify the package builds successfully with `npm run prepare`
- Review the GitHub Actions logs for specific errors

## 🎉 First Release

For your first release:

1. Set up the NPM_TOKEN secret (see Prerequisites)
2. Go to GitHub Actions → Release and Publish
3. Run workflow with "patch" release type
4. This will create version 0.1.1 and publish to npm

Your package will then be available for installation:
```bash
npm install react-native-crosssqlite
```
