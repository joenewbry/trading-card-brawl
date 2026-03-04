# Endless Modular TCG: Trading Card Brawl

## Core Design Philosophy

- **Depth over spectacle**: Every mechanic must reward mastery, not reaction speed. Patterns must be readable, counters learnable.
- **Elegant constraints**: Limitation breeds creativity. Deck building is not about stacking power—it’s about synergy under pressure.
- **Loss as progression**: Losing is not failure. It is data. Every defeat must feed the player’s understanding and collection.

## 1. Card Balance: Rock-Paper-Scissors Between Classes

Three core classes form a balanced triad:

- **Steel Vanguard** (Armor/Control): High health, slow attacks, disrupts tempo. Beats *Void Weavers* via resource denial.
- **Void Weavers** (Disruption/Debuff): Removes buffs, steals stats, delays effects. Beats *Ember Reapers* via burn and tempo collapse.
- **Ember Reapers** (Speed/Aggro): Low health, high damage, rapid attacks. Beats *Steel Vanguard* via overwhelm and burst.

Each class has 3 subclasses (e.g., Steel Vanguard: Sentinel, Bastion, Ironclad), each with unique synergies. Class matchups are deterministic and learnable. No RNG-based counters.

## 2. Deck Building Constraints

- Minimum deck size: 40 cards
- Maximum copies of any single card: 3
- No card duplication across classes (a card belongs to one class only)
- Decks must contain at least 2 classes (no mono-class decks)

These constraints enforce strategic diversity. Players cannot "spam the best card"—they must build synergistic chains under pressure. The 3-copy limit ensures variance in draws while allowing reliable combos.

## 3. Shuffling and Dealing Mechanics

- All decks are shuffled using a cryptographically secure procedural algorithm (Fisher-Yates with hardware entropy)
- No "streak detection" or "balancing"—each draw is statistically independent
- Initial hand: 5 cards
- Draw: 1 card per turn (no mulligan after turn 1)
- Top-deck manipulation is impossible. No "skill-based" card placement.

Fairness is non-negotiable. Skill is expressed in *adaptation*, not prediction.

## 4. Matchmaking System

- **Primary**: Real-time PvP matchmaking (15s timeout)
- **Fallback**: If no human opponent found within 15s, spawn a dynamic AI opponent
- AI difficulty scales with player win rate and deck complexity
- AI decks are constructed from the player’s own collection (using 80% of their owned cards, weighted by rarity and class)
- AI behavior mimics human patterns: aggressive players face aggressive AI, control players face disruptive AI

No "bot farm". AI is not a crutch—it’s a mirror.

## 5. Card Rarity System

- **Common (C)**: 60% drop rate — foundational cards, baseline effects
- **Uncommon (U)**: 25% drop rate — synergistic cards, minor twists
- **Rare (R)**: 12% drop rate — powerful effects, high cost, high risk
- **Mythic (M)**: 3% drop rate — game-defining cards, unique mechanics, high skill ceiling

Rarity is purely cosmetic in presentation. All cards are balanced for competitive play. Mythics are not "unbeatable"—they are high-skill, high-reward tools that require mastery to use properly.

## 6. Rewarding Loss: Progression Through Defeat

- After every match (win or loss), player earns **Battle Tokens** (1–5 based on match length and card efficiency)
- Tokens unlock tiers in a single progression track:
  - Tier 1–5: Common cards
  - Tier 6–12: Uncommon cards
  - Tier 13–18: Rare cards
  - Tier 19+: Mythic cards
- Match performance (e.g., "killed 3 units in 2 turns", "survived 7 turns with <5 HP") grants bonus tokens
- Lost matches grant 80% of the tokens a win would, ensuring consistent progression
- Players receive a "Defeat Insight" after each loss: "Your deck lacked tempo control. Try adding a Void Weaver disruption card."

Loss is not an endpoint—it is a diagnostic. The game does not reward winners; it rewards learners.

## Final Note

This is not a collection game. It is a *mastery* game. Every card drawn is a question. Every match is a lesson. Every loss is a step forward.

— Ikeda