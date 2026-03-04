# QA Test Plan for Sprint 2

## 1. Test Coverage Matrix

### AI Opponent
| Test ID | Description | Steps | Expected Result | Pass Criteria |
|---------|-------------|-------|-----------------|---------------|
| AI-01 | AI responds within 5s SLA | Start match, end turn, measure time until AI action appears | AI action appears within 5s | Time < 5000ms on 10 consecutive turns |
| AI-02 | AI doesn't cheat (no extra cards) | Play 10 matches, count total cards in AI hand | AI hand never exceeds 5 cards | Max 5 cards at any time |
| AI-03 | AI uses only player's owned cards | Player owns 10 cards, AI deck must only contain those | AI deck contains no unowned cards | All AI cards in player's collection |
| AI-04 | AI learns after 5 wins | Play 5 matches with aggressive deck, then 5 more | AI blocks more, saves big cards | AI plays defensively in matches 6-10 |
| AI-05 | AI fallback triggers after 15s timeout | Simulate no human opponents, start match | AI opponent spawns within 15s | Match starts with AI by 15.0s |
| AI-06 | AI doesn't overdraw | Player draws 1 card/turn, AI must do same | AI never draws more than 1 card per turn | AI draw count matches player draw count |
| AI-07 | AI respects mana cap | Player has 3 mana, AI cannot play 4-cost card | AI only plays cards ≤ available mana | AI never plays card exceeding current mana |
| AI-08 | AI gives card after loss | Lose a match, check inventory | Player receives 1 card post-match | New card appears in collection within 10s |
| AI-09 | AI doesn't use mythics as default | Player has 1 mythic, AI uses it ≤10% of games | AI plays mythic rarely | Mythic used ≤10% of total AI plays |
| AI-10 | AI respects class balance | Player uses Steel Vanguard, AI responds with Void Weaver | AI counters player's class appropriately | AI class counters player class 70%+ of time |

### Matchmaking
| Test ID | Description | Steps | Expected Result | Pass Criteria |
|---------|-------------|-------|-----------------|---------------|
| MM-01 | Match found within 15s (90% success) | 20 test accounts join queue, record match time | 18+ matches happen within 15s | 90% success rate over 20 tests |
| MM-02 | Matchmaking respects skill rating | High-skill player joins queue, matched with ±50 rating | Matched with similar skill level | ±50 rating difference |
| MM-03 | Matchmaking prioritizes low latency | Two players: one 100ms, one 300ms ping | Matched with lower latency if skill equal | Lower ping player matched first |
| MM-04 | Matchmaking respects class preference | Player sets preference: "Ember Reaper" | Matched with other Ember Reaper | Opponent class = preference 80%+ of time |
| MM-05 | Match timeout triggers AI fallback | Simulate 100% queue saturation | AI opponent spawns after 15s | AI appears at exactly 15.0s |
| MM-06 | Queue clears after match | After match starts, player removed from queue | Player no longer in matchmaking list | Player ID absent from Redis queue |
| MM-07 | Matchmaking rejects mono-class decks | Player tries to queue with Steel Vanguard only | Matchmaking rejects request | Error message: "Decks must contain 2+ classes" |
| MM-08 | Matchmaking rejects decks >40 cards | Player tries to queue with 41-card deck | Matchmaking rejects request | Error message: "Deck must be exactly 40 cards" |
| MM-09 | Matchmaking rejects 4x copies | Player tries to queue with 4x "Fireball" | Matchmaking rejects request | Error: "Max 3 copies per card" |
| MM-10 | Matchmaking latency sorting | Two players: same skill, 90ms vs 190ms | 90ms player matched first | Lower latency player selected |

### Tutorial
| Test ID | Description | Steps | Expected Result | Pass Criteria |
|---------|-------------|-------|-----------------|---------------|
| TUT-01 | Tutorial starts on first launch | Launch app fresh | Tutorial overlay appears | Tutorial UI visible, no main UI |
| TUT-02 | Step 1: Draw 5 cards | No action taken | 5 cards appear in hand | Hand contains exactly 5 cards |
| TUT-03 | Step 2: Play 1-cost card | Tap a 1-cost card and target | Card plays, mana reduced | Mana decreases by 1, card moves to board |
| TUT-04 | Step 3: Attack with minion | Tap minion → tap opponent | Minion attacks, opponent loses HP | Opponent HP decreases by minion's attack |
| TUT-05 | Step 4: End turn | Tap "End Turn" | Turn ends, opponent's turn begins | Player mana refills, opponent's turn starts |
| TUT-06 | Step 5: Win match | Let AI take 1 turn, then win | "You Win" screen appears | Win screen triggers, AI doesn't act |
| TUT-07 | Tutorial gives card after step 1 | After drawing 5 cards | Player receives 1 Common card | Card appears in collection immediately |
| TUT-08 | Tutorial gives card after step 2 | After playing 1-cost card | Player receives 1 Uncommon card | Card appears in collection |
| TUT-09 | Tutorial gives card after step 3 | After attacking with minion | Player receives 1 Rare card | Card appears in collection |
| TUT-10 | Tutorial gives card after step 5 | After winning match | Player receives 1 Mythic card | Card appears in collection |
| TUT-11 | Tutorial cannot be skipped | Tap anywhere outside tutorial | No action | Tutorial remains active |
| TUT-12 | Tutorial resets after reset | Clear app data, relaunch | Tutorial appears again | Tutorial UI visible |
| TUT-13 | Tutorial doesn't appear after completion | Launch app after completing tutorial | Main game UI loads | No tutorial overlay |
| TUT-14 | Tutorial works on mobile | Run on iPhone 13 | Touch targets respond | All steps functional with tap/swipe |
| TUT-15 | Tutorial works on desktop | Run on Chrome desktop | Mouse clicks work | All steps functional with click/drag |

### Save System
| Test ID | Description | Steps | Expected Result | Pass Criteria |
|---------|-------------|-------|-----------------|---------------|
| SAVE-01 | Local save on quit | Play 1 match, close browser | Save file persists in IndexedDB | File exists after reload |
| SAVE-02 | Save syncs on reconnect | Disconnect network, play match, reconnect | Changes sync to server | Server state matches client |
| SAVE-03 | Conflict resolution: server wins | Modify save file locally, sync | Server data overwrites local | Local changes discarded |
| SAVE-04 | Conflict resolution: client wins (preferences) | Change UI volume locally, sync | Local volume setting preserved | Volume setting unchanged |
| SAVE-05 | Save file encrypted | Inspect IndexedDB content | Save data is encrypted | No readable JSON in storage |
| SAVE-06 | Save file < 100KB | Collect 50 cards, check save size | Size ≤ 100KB | File size ≤ 100,000 bytes |
| SAVE-07 | Save loads after reboot | Close browser, reopen | Saved deck and collection restored | All cards and decks present |
| SAVE-08 | Save syncs with JWT token | Log out, log back in with same account | Saved data restored | Collection unchanged |
| SAVE-09 | Save prevents double-spend | Spend 4 mana, try to play 3-cost card | Action blocked | Error: "Not enough mana" |
| SAVE-10 | Save syncs after network loss | Play 3 turns offline, reconnect | All actions sync | Match state correct on server |

### WebGL
| Test ID | Description | Steps | Expected Result | Pass Criteria |
|---------|-------------|-------|-----------------|---------------|
| WEB-01 | WebGL loads in <5s | Load game on Chrome desktop | Page renders game UI within 5s | Time from tab open to first frame <5000ms |
| WEB-02 | WebGL runs at 60fps on mid-tier mobile | Run on Pixel 7 | Frame rate ≥60fps | Avg FPS ≥60 over 30s |
| WEB-03 | WebGL runs at ≥30fps on low-end mobile | Run on iPhone 13 | Frame rate ≥30fps | Avg FPS ≥30 over 30s |
| WEB-04 | Card art loads without delay | Tap card in hand | Card animation plays instantly | No loading spinner, no texture pop |
| WEB-05 | Audio plays on WebGL | Play card | Sound triggers | Audio heard (no mute) |
| WEB-06 | Touch targets ≥48px | Tap on card (iPhone 13) | Card selected | Touch area ≥48x48px (verified via dev tools) |
| WEB-07 | WebGL fails gracefully on unsupported | Open on old Android device | Fallback message appears | "Your device is not supported" shown |
| WEB-08 | WebGL asset chunking | Load game, wait 5s, play card | Card art loads after initial render | Card art not in initial bundle |
| WEB-09 | WebGL memory usage ≤1.5GB | Play 10 matches, monitor memory | Memory ≤1.5GB | No crash, no browser tab freeze |
| WEB-10 | WebGL pauses on tab switch | Switch to other tab, return | Game pauses, resumes | Game state preserved, no crash |

### Audio
| Test ID | Description | Steps | Expected Result | Pass Criteria |
|---------|-------------|-------|-----------------|---------------|
| AUD-01 | Card play sound triggers | Tap and play card | Sound plays | Audio heard |
| AUD-02 | Attack sound triggers | Attack with minion | Sound plays | Audio heard |
| AUD-03 | Win jingle triggers | Win match | Jingle plays | Audio heard |
| AUD-04 | Lose jingle triggers | Lose match | Jingle plays | Audio heard |
| AUD-05 | Ambient loop plays | Start match | Continuous loop | No gaps, no clicks |
| AUD-06 | Audio volume balance | Turn music to 50%, SFX to 100% | SFX louder than music | Music doesn't drown SFX |
| AUD-07 | Audio works on iOS | Play on iPhone 13 | Sounds play | No mute, no distortion |
| AUD-08 | Audio works on Android | Play on Pixel 7 | Sounds play | No mute, no distortion |
| AUD-09 | Audio works on desktop | Play on Chrome | Sounds play | No mute, no distortion |
| AUD-10 | Audio stops on mute | Toggle mute button | All sounds silenced | No audio output |
| AUD-11 | Audio resumes on unmute | Toggle mute off | Sounds return | Audio resumes normally |
| AUD-12 | Audio loops cleanly | Let ambient play 60s | No audible glitch | Zero dropouts or pops |
| AUD-13 | Audio doesn't overload CPU | Play 10 matches with all SFX | CPU usage ≤70% | No performance degradation |
| AUD-14 | Audio loads from CDN | Load game | Audio files loaded from CDN | Network tab shows .ogg from CDN |
| AUD-15 | Audio format = OGG | Inspect asset files | All audio files are .ogg | No .wav, .mp3, or .aiff |


## 2. Regression Suite (Run After Every Merge)

| Test ID | Description | Steps | Expected Result | Pass Criteria |
|---------|-------------|-------|-----------------|---------------|
| REG-01 | Mana Refill | Start match, end turn, check mana | Mana refills exactly 1 of each type | Mana levels: 1/1/1/1 per turn |
| REG-02 | Win Condition | Reduce opponent HP to 0 | Match ends, win screen triggers | Game state changes to "WIN" |
| REG-03 | Deck Shuffle | Start match, record first 5 cards | Each draw is random | No predictable sequence in 50 runs |
| REG-04 | Card Schema Validation | Replace card JSON with invalid field | Game refuses to load | Error message: "Invalid card schema" |


## 3. Device Matrix

| Feature | iPhone 13 | Pixel 7 | iPad | Chrome Desktop | Safari Desktop |
|---------|-----------|---------|------|----------------|----------------|
| AI Opponent | ✅ | ✅ | ✅ | ✅ | ✅ |
| Matchmaking | ✅ | ✅ | ✅ | ✅ | ✅ |
| Tutorial | ✅ | ✅ | ✅ | ✅ | ✅ |
| Save System | ✅ | ✅ | ✅ | ✅ | ✅ |
| WebGL | ✅ | ✅ | ✅ | ✅ | ✅ |
| Audio | ✅ | ✅ | ✅ | ✅ | ✅ |
| Touch Targets | ✅ | ✅ | ✅ | N/A | N/A |
| Mobile Responsiveness | ✅ | ✅ | ✅ | N/A | N/A |
| Performance (60fps) | ✅ | ✅ | ✅ | N/A | N/A |
| Load Time (<5s) | ✅ | ✅ | ✅ | ✅ | ✅ |


## 4. Performance Benchmarks

| Metric | Target | Measurement Method |
|--------|--------|---------------------|
| WebGL Load Time | < 5 seconds | Measure from tab open to first frame (Chrome DevTools Performance tab) |
| AI Response Time | < 5 seconds | Time from turn end to AI action on server (log timestamp) |
| Matchmaking Time | < 15 seconds | Time from queue join to match start (server logs) |
| Frame Rate | ≥60fps on mid-tier mobile | Measure average FPS over 30s on Pixel 7 (Chrome DevTools) |
| Save File Size | ≤100 KB | Inspect IndexedDB content size |
| Card Art Load Time | < 500ms from CDN | Network tab: time from card tap to asset load complete |
| Audio Latency | < 200ms | Time from action to audio playback (using audio waveform analysis) |


## 5. Edge Cases

| Test ID | Description | Steps | Expected Result | Pass Criteria |
|---------|-------------|-------|-----------------|---------------|
| EC-01 | Empty Deck Draw | Play until deck is empty | Draw 0 cards, show "Deck empty" | No crash, no error, UI shows message |
| EC-02 | 0HP Simultaneous | Both players hit 0HP on same turn | Draw declared | Match ends in tie, "Draw" screen |
| EC-03 | AI Timeout Fallback | AI server down for 10s | AI responds with "default" action (e.g., end turn) | Game continues, AI makes safe move |
| EC-04 | Save Conflict Resolution | Two devices modify save simultaneously | Server wins core data, client wins preferences | Collection and decks from server; volume and UI from client |
| EC-05 | Network Disconnect Mid-Match | Disconnect Wi-Fi during match | Game pauses, auto-saves, reconnects | Match resumes, state preserved |
| EC-06 | Invalid Card Schema (Missing ID) | Load card without "id" field | Game refuses to load | Error: "Card must have unique ID" |
| EC-07 | Invalid Mana Cost (Negative) | Load card with cost: -1 | Game refuses to load | Error: "Mana cost must be ≥0" |
| EC-08 | Deck Size 39 | Attempt to start match with 39 cards | Game rejects | Error: "Deck must be exactly 40 cards" |
| EC-09 | Deck Size 41 | Attempt to start match with 41 cards | Game rejects | Error: "Deck must be exactly 40 cards" |
| EC-10 | 4th Copy of Card | Try to add 4th copy of card to deck | Game rejects | Error: "Max 3 copies allowed" |
| EC-11 | Mono-Class Deck | Try to queue with only Steel Vanguard | Game rejects | Error: "Decks must contain 2+ classes" |
| EC-12 | Unowned Card in Deck | Player tries to use card not in collection | Game refuses to play | Error: "Card not in collection" |
| EC-13 | No Internet on Launch | Launch app offline | Load local save, disable sync | Game loads, sync disabled with warning |
| EC-14 | Invalid JWT Token | Modify saved JWT | Sync fails, prompt login | User reauthenticates |
| EC-15 | High Latency Match | Simulate 500ms ping | Match still proceeds | AI fallback works, no crash |
| EC-16 | Browser Tab Background | Switch to other tab during turn | Game pauses, resumes | Turn state preserved |
| EC-17 | Low Memory (1GB RAM) | Run on low-end device | Game reduces asset quality | Cards load slower, no crash |
| EC-18 | 100% CPU on Server | Simulate 1000 AI requests | AI queue delays, but doesn't crash | AI responds with 10s delay, game continues |
| EC-19 | Corrupt Card JSON | Replace one card file with random bytes | Game skips card, logs error | Card appears as "?" with warning |
| EC-20 | Multiple Save Conflicts | 3 devices sync at once | Server resolves based on timestamp | Most recent wins, no data loss |


> **Total Test Cases**: 80 (exceeding 40 required)


## Next Steps

- [ ] `git add -A`
- [ ] `git commit -m 'docs: QA test plan for Sprint 2'`
- [ ] `git push origin main`