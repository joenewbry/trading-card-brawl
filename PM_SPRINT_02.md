# Sprint 2: Core Systems & Scalability

## Goals
Build the systems that enable multiplayer, persistence, and polished production: **AI opponent, matchmaking, tutorial, save system, audio, WebGL build, and CI/CD**. This sprint delivers a fully functional, production-ready prototype with automated testing and cross-device compatibility.

### What Gets Built
- **AI Opponent System** — DGX Spark integration: state snapshot → AI response → server applies
- **Matchmaking System** — PvP queue with 15s timeout → AI fallback
- **Tutorial System** — 5-step guided onboarding with card rewards
- **Save System** — IndexedDB local storage + OpenArcade cloud sync
- **Audio/SFX** — Placeholder sounds: card play, attack, win/lose jingle, ambient loop
- **WebGL Build Pipeline** — UE5 export configured for mobile/web performance
- **CI/CD Pipeline** — GitHub Actions: build check + lint on every PR

## Task Breakdown

| Task ID | Title | Description | Assigned To | Status | Priority | Due Date | Notes |
|---------|-------|-------------|-------------|--------|----------|----------|-------|
| 51 | AI State Snapshot Protocol | Implement JSON serializer for game state to send to DGX Spark. Include: hand, board, mana, HP, deck size, turn number, player ID. | arcade-dev-02 | Not Started | High | 2026-03-20 | 
| 52 | AI Response Deserializer | Implement C++ deserializer for AI action responses. Parse JSON array of actions and inject into game loop. | arcade-dev-02 | Not Started | High | 2026-03-20 | 
| 53 | WebGL Build Test | Test WebGL build on iOS Safari, Android Chrome, Windows Firefox, Mac Safari. Measure load time, fps, memory usage. Fix bottlenecks. | tech-architect | Not Started | High | 2026-03-21 | 
| 54 | WebGL Asset Chunking | Implement asset chunking: preload core assets, load card art and animations on demand. Use Webpack or UE5 streaming. | tech-architect | Not Started | High | 2026-03-21 | 
| 55 | Save System Encryption | Implement AES-256-GCM encryption for save data using user's OpenArcade JWT token as key. Use CryptoAPI in browser. | arcade-dev-02 | Not Started | High | 2026-03-21 | 
| 56 | Save System Sync Logic | Implement sync logic: client sends last sync timestamp. Server returns changes. Merge client changes on reconnect. Conflict: server wins for core data. | arcade-dev-02 | Not Started | High | 2026-03-21 | 
| 57 | CI/CD Unit Tests | Implement unit tests for card schema, mana system, and game loop in C++. Run on every PR. Require 95% coverage. | arcade-dev-01 | Not Started | High | 2026-03-22 | 
| 58 | CI/CD WebGL Test | Implement GitHub Action that triggers UE5 WebGL build, then runs automated test via Puppeteer. Fail if load time > 5s or fps < 30. | arcade-dev-01 | Not Started | High | 2026-03-22 | 
| 59 | PR Workflow Enforcement | Implement branch protection rule: main branch requires 2 approvals, CI must pass, no force pushes. | arcade-dev-03 | Not Started | High | 2026-03-22 | 
| 60 | PR Reviewer Assignment | Configure GitHub team reviewers: each PR must be assigned to 2 from dev-team and 1 from design-team. | arcade-dev-03 | Not Started | High | 2026-03-22 | 
| 68 | UI Audio Integration | Integrate placeholder audio files into Blueprint events: card play, attack, win, lose, mana refill. | arcade-dev-03 | Not Started | Medium | 2026-03-22 | 
| 69 | QA: Tutorial Flow | Test tutorial from start to finish. Ensure no buttons, no menus, no confusion. Each step ends with correct card gift. |  | Not Started | High | 2026-03-24 | 
| 70 | QA: Matchmaking Speed | Test matchmaking: 10 test accounts. Confirm 90% match within 15s. Log timeouts. |  | Not Started | High | 2026-03-24 | 
| 71 | QA: Mobile Responsiveness | Test UI on 5 devices: iPhone 13, Pixel 7, iPad, Windows tablet, Chromebook. Confirm touch targets, gestures, performance. |  | Not Started | High | 2026-03-24 | 
| 72 | QA: Save System Sync | Test save sync: disconnect network, make changes, reconnect. Confirm changes sync correctly. Test conflict resolution. |  | Not Started | High | 2026-03-24 | 
| 73 | QA: WebGL Performance | Test WebGL build on 3 low-end devices. Confirm fps > 30, load time < 6s, no crashes. |  | Not Started | High | 2026-03-24 | 
| 74 | QA: Card Schema Validation | Test schema validation: corrupt card JSON, load game. Confirm error thrown and game refuses to start. |  | Not Started | High | 2026-03-24 | 
| 75 | QA: AI Behavior | Test AI: 10 matches. Confirm it plays reasonably, never overdraws, never cheats, learns after 5 wins. |  | Not Started | High | 2026-03-24 | 
| 76 | QA: Audio Looping | Test ambient music and jingles loop cleanly. No clicks, no gaps. |  | Not Started | Medium | 2026-03-24 | 
| 77 | QA: PR Workflow | Test PR workflow: create branch, push, open PR, approve, merge. Confirm branch protection works. |  | Not Started | High | 2026-03-24 | 
| 78 | QA: CI/CD Pipeline | Test CI/CD: push to branch, verify unit tests run, WebGL build triggers, staging deploys. |  | Not Started | High | 2026-03-24 | 
| 79 | QA: Mobile Audio | Test audio on mobile devices. Confirm sound plays, no mute issues. |  | Not Started | Medium | 2026-03-24 | 
| 80 | QA: Card Art Load | Test card art loads correctly in game. No broken textures, no misalignment. |  | Not Started | High | 2026-03-24 | 
| 88 | QA: Mobile Touch Targets | Confirm all buttons are at least 48x48px on all mobile devices. |  | Not Started | High | 2026-03-24 | 
| 89 | QA: Save File Size | Confirm save file < 100KB after 50 cards collected. |  | Not Started | Medium | 2026-03-24 | 
| 90 | QA: CDN Card Load | Confirm card JSON loads from CDN in < 500ms on 3G. |  | Not Started | High | 2026-03-24 | 
| 91 | QA: WebSockets Stability | Test WebSocket connection: disconnect and reconnect 10 times. Confirm game state recovers. |  | Not Started | High | 2026-03-24 | 
| 94 | QA: Matchmaking Class Preference | Confirm matchmaking respects class preference (if set). |  | Not Started | High | 2026-03-24 | 
| 95 | QA: Turn End Animation | Confirm turn end animation plays smoothly and doesn't block input. |  | Not Started | High | 2026-03-24 | 
| 96 | QA: Mana Refill | Confirm mana refills exactly 1 of each type per turn. No overshoot, no delay. |  | Not Started | High | 2026-03-24 | 
| 97 | QA: No Random Draws | Confirm no card is drawn from deck unless player plays "Draw" action. No hidden draws. |  | Not Started | High | 2026-03-24 | 
| 99 | QA: Deck Size Limit | Confirm deck can't exceed 40 cards. Can't play 4th copy of a card. |  | Not Started | High | 2026-03-24 | 
| 100 | QA: No Mono-Class | Confirm deck must have at least 2 classes. Prevent single-class deck creation. |  | Not Started | High | 2026-03-24 | 
| 104 | QA: Card Tooltip | Ensure card tooltip shows name, cost, attack/health, description, and abilities clearly. |  | Not Started | Medium | 2026-03-24 | 
| 105 | QA: Matchmaking Latency Sorting | Confirm matchmaking prioritizes low-latency players when skill is equal. |  | Not Started | High | 2026-03-24 | 
| 107 | QA: Save Load on Reboot | Confirm saved game loads correctly after closing and reopening browser. |  | Not Started | High | 2026-03-24 | 
| 108 | QA: No Double-Spend | Confirm you can't spend more mana than you have. No glitches. |  | Not Started | High | 2026-03-24 | 
| 110 | QA: Audio Volume Balance | Ensure SFX and music volume is balanced. No music drowning out SFX. |  | Not Started | Medium | 2026-03-24 | 
| 111 | Implement Tutorial System (Blueprint) | Implement 5-step tutorial: 1) Draw 5 cards, 2) Play card with 1 mana, 3) Attack with minion, 4) End turn, 5) Win. Each step ends with card gift. No UI buttons. | arcade-dev-03 | Not Started | High | 2026-03-21 | 
| 112 | Implement AI Opponent | AI plays predictably at first (safe, kind). After 5 wins, learns to block, save big cards, play smart. Never cheats, never has more cards. Gives new card after defeat. | arcade-dev-02 | Not Started | High | 2026-03-20 | 
| 113 | Implement Matchmaking Module (C++) | Implement matchmaking system using Redis. Queue players by skill, latency, class preference. Match within 15s. Fallback to AI. | arcade-dev-02 | Not Started | High | 2026-03-20 | 
| 114 | Implement Audio/SFX/Music System | Implement placeholder audio: card play sound, attack sound, win/lose jingle, ambient music. Use OGG format. Trigger via events in Blueprint. | game-artist | Not Started | Medium | 2026-03-22 | 
| 115 | Implement WebGL Build Pipeline | Configure UE5 project for WebGL export: ETC2 compression, WASM build, asset chunking, code stripping. Test on Chrome, Safari, Firefox. Target 60fps on mid-tier mobile. | tech-architect | Not Started | High | 2026-03-21 | 
| 116 | Implement CI/CD Pipeline | Set up GitHub Actions CI/CD: test card schema, test WebGL build, run unit tests, deploy to staging on PR merge. Auto-deploy to prod on tag. | arcade-dev-01 | Not Started | High | 2026-03-22 | 

## Definition of Done for Sprint 2

✅ AI Opponent integrates with DGX Spark and responds within 5s SLA
✅ Matchmaking queue resolves 90% of PvP matches within 15s, with AI fallback
✅ Tutorial completes all 5 steps without UI buttons; player receives card after each step
✅ Save system: local IndexedDB + cloud sync with AES-256 encryption, conflict resolution
✅ All audio placeholders implemented and triggered correctly (card play, attack, win/lose, ambient)
✅ WebGL build exports successfully, runs at 60fps on mid-tier mobile, loads in <5s
✅ CI/CD pipeline runs on every PR: lint, schema test, WebGL build test, unit test coverage >95%
✅ All tasks in `TASK_TRACKER.csv` for Sprint 2 marked "Not Started" or "In Progress" — none left unassigned

## Dependencies on Sprint 1

- **Card JSON Schema** must be merged and validated before AI, save, or CDN can work
- **Mana System** must be fully implemented and stable before tutorial or game loop can be tested
- **Core Game Loop** (Draw → Play → Fight → End Turn) must be functional for AI and matchmaking to simulate matches
- **UI Skeleton** must exist to integrate tutorial UI and audio triggers
- **All 30 Class Cards** must be designed and in `/cards/` before AI can use them for deck building

> **Note**: All Sprint 1 items must be marked "Done" in `TASK_TRACKER.csv` before Sprint 2 can be considered ready for development. No Sprint 2 task may begin until its dependencies are merged to `main`.