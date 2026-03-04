# Sprint 1: Core Foundations

## Goals
Build the foundational system that enables gameplay: **card design, mana system, game loop, and basic UI**. This sprint delivers a playable prototype with 6 classes (30 cards), 5 mana types, and turn-based combat.

### What Gets Built
- **All 30 class cards** (6 classes × 5 cards each) — fully designed and balanced
- **Mana system implementation** — 5 mana types, predictable refill
- **Core game loop** — draw → play → fight → end turn
- **Basic combat system** — visual attack feedback, health reduction
- **Card JSON schema** — validated, versioned, stored
- **UI skeleton** — hand, board, mana bar, turn counter (mobile/desktop responsive)

## Assigned Agents

| Task | Agent |
|------|-------|
| Design Necromancer cards (5) | game-designer-ikeda |
| Design Warrior cards (5) | game-designer-ikeda |
| Design Rogue cards (5) | arcade-agent-03 |
| Design Druid cards (5) | game-designer-miyamoto |
| Design Engineer cards (5) | arcade-agent-03 |
| Design Ranger cards (5) | game-designer-miyamoto |
| Implement Shadow Mana | arcade-dev-01 |
| Implement Steel Mana | arcade-dev-01 |
| Implement Life Mana | arcade-dev-01 |
| Implement Wind Mana | arcade-dev-02 |
| Implement Earth Mana | arcade-dev-02 |
| Implement Card JSON Schema | tech-architect |
| Implement Game Loop (Blueprint) | arcade-dev-01 |
| Implement Combat System (Blueprint) | arcade-dev-01 |
| Implement UI Module (Blueprint) | arcade-dev-03 |
| Art: 30 Class Cards | game-artist |
| Art: Mana Symbols | game-artist |
| Card Storage & CDN Setup | tech-architect |
| Schema Validation (C++) | arcade-dev-01 |

## Definition of Done

✅ All 30 cards designed and documented in `TASK_TRACKER.csv` (approved by designers) 
✅ All 5 mana types implemented, refilling correctly each turn 
✅ Game loop: Draw → Play → Fight → End Turn works end-to-end 
✅ Combat: Attacks trigger visual feedback (damage numbers, particle effects) 
✅ All cards stored as JSON in `/cards/` with schema validation 
✅ UI shows hand, board, mana, turn counter — responsive on mobile and desktop 
✅ All artwork delivered (2K PNG, transparent) and integrated into engine 
✅ Card JSON schema validated on load — invalid cards rejected 
✅ All tasks in `TASK_TRACKER.csv` with priority "High" for Sprint 1 are marked "In Progress" or "Done" 

> **Note**: No AI opponent, no save system, no tutorial, no audio, and no WebGL build are required for Sprint 1. These are Sprint 2.

> **Final Check**: A developer must be able to start the game, draw 5 cards, play one, attack, end turn — and see the opponent’s turn begin (even if AI is placeholder). That’s the bar.