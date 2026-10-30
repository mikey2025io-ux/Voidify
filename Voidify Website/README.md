# Voidify — GitHub + Netlify + app downloads

## Deploy
1. Push this entire folder to a GitHub repository (including `.github`).
2. Connect the repository to Netlify. Build command: `npm run build`; publish directory: `.`.
3. In Firebase Console, enable Authentication > Google, add your Netlify domain to authorized domains, and fill in `firebase-config.js`.
4. Put MP3/MP4/WebM files in `Video/` and push; Netlify generates `catalog.json` during deployment.
5. In GitHub repository Settings > Secrets and variables > Actions > Variables, add `VOIDIFY_SITE_URL` with your complete HTTPS Netlify site URL (for example `https://voidify.netlify.app`).
6. In `index.html`, replace `OWNER/REPO` in both download URLs with your GitHub username and repository name.
7. Create and push a tag `v1.0.0` or run Actions > Build Voidify apps > Run workflow. Tags publish assets to GitHub Releases; manual runs make downloadable workflow artifacts.

## Platforms
- Browser/PWA: use Install App in supported browsers.
- Android: download `Voidify-Android.apk` from GitHub Releases. This is a **debug-signed APK** for testing, not a Play Store release. Android will require permission to install it.
- Windows: download `Voidify-Windows.zip`, extract and run `Voidify.exe`. Requires Microsoft Edge WebView2 Runtime (included on most current Windows machines).

## Limitations
- Both native wrappers load the live Netlify website. The PWA provides the best offline shell support; full offline media requires downloading individual tracks from the website. The Android WebView and Windows WebView2 offline behavior may differ.
- Google Firebase popup sign-in may not work in embedded WebViews; use the browser/PWA for Google sign-in, or implement native OAuth flows for production Android and Windows apps.
- A GitHub release URL downloads the APK/ZIP but cannot silently install it.
- Large media files can exceed GitHub and Netlify repository/deploy size limits. Use object storage for large libraries.
- A debug APK is not production-signed. For public distribution, configure an Android signing key and verify release builds.
