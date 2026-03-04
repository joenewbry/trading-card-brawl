# Trading Card Brawl — Setup Guide
**Engine:** Unreal Engine 5.7  
**Asset Pack:** Endless Modular TCG Trading Card Collection (Fab)

---

## Step 1: Open the Project

```bash
cd /Users/joe/dev/openarcade/trading-card-brawl
./build.sh
```

Or just double-click `TradingCardBrawl.uproject`.

UE5.7 will detect the C++ source and ask to build — **click Yes**.  
First compile takes ~5-10 minutes.

---

## Step 2: Add the Fab Asset Pack

Once the editor is open:

1. **Window → Fab** (top menu bar)
2. Click **My Library** (top right of the Fab panel)
3. Search for **"Endless Modular TCG"**
4. Click **Add to Project** → select TradingCardBrawl → confirm
5. Assets will appear in `Content/EndlessModularTCGTradingCardCollection/`

---

## Step 3: What You'll Find in the Pack

| Folder | Contents |
|--------|----------|
| `Artwork/Assassin/` | Rogue card portraits |
| `Artwork/Druid/` | Druid card portraits |
| `Artwork/Hunter/` | Ranger card portraits |
| `Artwork/Mech/` | Engineer card portraits |
| `Artwork/Warlock/` | Necromancer card portraits |
| `Artwork/Warriors/` | Warrior card portraits |
| `Artwork/Spells/` | Spell card portraits |
| `CardBacks/` | 157 card back designs |
| `CardBorders/` | 21 border frames |
| `CharacterIcons/` | 154 hero portrait icons |
| `Icons/` | 102 ability/mana icons |

---

## Step 4: After Assets Are In

Let me know and I'll:
- Wire up the `BP_CardWidget` Blueprint to layer Border + Portrait + Text
- Map each of our 30 cards to specific artwork from the pack
- Set up the hero class selection screen using the CharacterIcons
- Build the first in-editor playable level

---

## Class → Asset Pack Mapping

| Our Class | Pack Folder | Notes |
|-----------|------------|-------|
| Warrior | `Artwork/Warriors/` | Steel mana, tank/defense theme |
| Ranger | `Artwork/Hunter/` | Wind mana, mobility theme |
| Necromancer | `Artwork/Warlock/` | Shadow mana, dark magic theme |
| Druid | `Artwork/Druid/` | Life mana, nature theme |
| Rogue | `Artwork/Assassin/` | Shadow+Wind, stealth theme |
| Engineer | `Artwork/Mech/` | Earth mana, construct theme |

---

## Project Structure

```
TradingCardBrawl.uproject     ← UE5.7, open this
Source/                       ← All C++ (23 modules, ~3,500 LOC)
  Cards/        ManaSystem, DeckManager, CardLoader, CardSchema, CardAssetStreamer
  GameModes/    TCBGameMode, TCBPlayerController, TCBGameSession
  AI/           AIStateSerializer, AIResponseHandler, AIOpponentController
  Matchmaking/  MatchmakingComponent
  Save/         TCBSaveGame, TCBSaveManager
  UI/           TCBHUD, CardWidget, ManaWidget, TutorialManager, AudioManager, DeckBuilder
Content/
  Cards/index.json   ← 30 card definitions (ready)
  Cards/Art/         ← Our 6 Gemini-generated artworks
prototype/           ← Working browser prototype (open index.html to play now)
```
