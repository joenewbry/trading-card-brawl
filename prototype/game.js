const CARDS = [
  { id: 'iron-vow', name: 'Iron Vow', class: 'warrior', cost: 1, attack: 1, health: 2, type: 'minion', abilities: [] },
  { id: 'shield-wall', name: 'Shield Wall', class: 'warrior', cost: 2, attack: 0, health: 5, type: 'minion', abilities: ['taunt'] },
  { id: 'counter-strike', name: 'Counter Strike', class: 'warrior', cost: 3, attack: 3, health: 3, type: 'minion', abilities: [] },
  { id: 'ironclad', name: 'Ironclad', class: 'warrior', cost: 4, attack: 4, health: 6, type: 'minion', abilities: ['taunt'] },
  { id: 'iron-oath', name: 'Iron Oath', class: 'warrior', cost: 6, attack: 6, health: 8, type: 'minion', abilities: ['divine_shield'] },

  { id: 'swift-shot', name: 'Swift Shot', class: 'ranger', cost: 1, attack: 2, health: 1, type: 'minion', abilities: [] },
  { id: 'wind-trap', name: 'Wind Trap', class: 'ranger', cost: 2, attack: 0, health: 0, type: 'spell', abilities: ['deal3'] },
  { id: 'shadowstep-arrow', name: 'Shadowstep Arrow', class: 'ranger', cost: 3, attack: 3, health: 2, type: 'minion', abilities: ['stealth'] },
  { id: 'galewing', name: 'Galewing', class: 'ranger', cost: 4, attack: 4, health: 3, type: 'minion', abilities: ['windfury'] },
  { id: 'whisperwind', name: 'Whisperwind', class: 'ranger', cost: 5, attack: 5, health: 4, type: 'minion', abilities: ['stealth', 'windfury'] },

  { id: 'grave-whisper', name: 'Grave Whisper', class: 'necromancer', cost: 1, attack: 1, health: 1, type: 'minion', abilities: ['deathrattle'] },
  { id: 'soul-drain', name: 'Soul Drain', class: 'necromancer', cost: 2, attack: 0, health: 0, type: 'spell', abilities: ['drain3hp'] },
  { id: 'bone-golem', name: 'Bone Golem', class: 'necromancer', cost: 3, attack: 3, health: 4, type: 'minion', abilities: [] },
  { id: 'lich-knight', name: 'Lich Knight', class: 'necromancer', cost: 4, attack: 5, health: 3, type: 'minion', abilities: ['lifesteal'] },
  { id: 'lord-of-death', name: 'Lord of Death', class: 'necromancer', cost: 6, attack: 7, health: 6, type: 'minion', abilities: ['lifesteal'] },

  { id: 'mosshide', name: 'Mosshide', class: 'druid', cost: 1, attack: 1, health: 3, type: 'minion', abilities: [] },
  { id: 'healing-bloom', name: 'Healing Bloom', class: 'druid', cost: 2, attack: 0, health: 0, type: 'spell', abilities: ['heal4'] },
  { id: 'ancient-treant', name: 'Ancient Treant', class: 'druid', cost: 3, attack: 2, health: 6, type: 'minion', abilities: ['taunt'] },
  { id: 'grove-sentinel', name: 'Grove Sentinel', class: 'druid', cost: 4, attack: 4, health: 5, type: 'minion', abilities: [] },
  { id: 'world-tree', name: 'World Tree', class: 'druid', cost: 6, attack: 5, health: 10, type: 'minion', abilities: ['taunt', 'lifesteal'] },

  { id: 'backstab', name: 'Backstab', class: 'rogue', cost: 1, attack: 2, health: 1, type: 'minion', abilities: ['stealth'] },
  { id: 'smoke-bomb', name: 'Smoke Bomb', class: 'rogue', cost: 2, attack: 0, health: 0, type: 'spell', abilities: ['stealth-all'] },
  { id: 'shadow-step', name: 'Shadow Step', class: 'rogue', cost: 2, attack: 3, health: 1, type: 'minion', abilities: ['stealth'] },
  { id: 'blade-dance', name: 'Blade Dance', class: 'rogue', cost: 4, attack: 4, health: 3, type: 'minion', abilities: ['windfury'] },
  { id: 'veil-stalker', name: 'Veil Stalker', class: 'rogue', cost: 5, attack: 6, health: 3, type: 'minion', abilities: ['stealth', 'windfury'] },

  { id: 'gear-sprite', name: 'Gear Sprite', class: 'engineer', cost: 1, attack: 1, health: 2, type: 'minion', abilities: [] },
  { id: 'iron-turret', name: 'Iron Turret', class: 'engineer', cost: 2, attack: 2, health: 3, type: 'minion', abilities: ['taunt'] },
  { id: 'overclock', name: 'Overclock', class: 'engineer', cost: 3, attack: 0, health: 0, type: 'spell', abilities: ['deal4'] },
  { id: 'clockwork-sentinel', name: 'Clockwork Sentinel', class: 'engineer', cost: 4, attack: 3, health: 6, type: 'minion', abilities: ['taunt'] },
  { id: 'clockwork-titan', name: 'Clockwork Titan', class: 'engineer', cost: 7, attack: 8, health: 8, type: 'minion', abilities: ['taunt', 'divine_shield'] }
];

const CLASS_NAMES = ['warrior', 'ranger', 'necromancer', 'druid', 'rogue', 'engineer'];

let state = {
  playerHP: 30,
  aiHP: 30,
  playerMana: 3,
  aiMana: 3,
  maxMana: 3,
  playerHand: [],
  playerBoard: [],
  aiHand: [],
  aiBoard: [],
  playerDeck: [],
  aiDeck: [],
  turn: 'player',
  selectedCard: null,
  selectedBoardCard: null,
  gameOver: false,
  playerClass: null,
  aiClass: null,
  message: ''
};

const ui = {};

function getByAnyId(...ids) {
  for (const id of ids) {
    const el = document.getElementById(id);
    if (el) return el;
  }
  return null;
}

function setupUiReferences() {
  ui.classSelectScreen = getByAnyId('class-select', 'class-select-screen');
  ui.gameScreen = getByAnyId('game-screen');
  ui.gameOverScreen = getByAnyId('game-over', 'game-over-screen');

  ui.aiHP = getByAnyId('ai-hp', 'ai-hp-text');
  ui.playerHP = getByAnyId('player-hp', 'player-hp-text');
  ui.aiHPFill = getByAnyId('ai-hp-fill');
  ui.playerHPFill = getByAnyId('player-hp-fill');

  ui.aiHand = getByAnyId('ai-hand');
  ui.aiBoard = getByAnyId('ai-board');
  ui.playerBoard = getByAnyId('player-board');
  ui.hand = getByAnyId('hand', 'player-hand');

  ui.manaDisplay = getByAnyId('mana-display', 'mana-counter');
  ui.turnIndicator = getByAnyId('turn-indicator');
  ui.classVs = getByAnyId('class-vs');
  ui.message = getByAnyId('message');

  ui.endTurnBtn = getByAnyId('end-turn-btn');
  ui.attackBtn = getByAnyId('attack-btn');
  ui.playBtn = getByAnyId('play-btn', 'play-card-btn');

  ui.classList = getByAnyId('class-list');
  ui.resultText = getByAnyId('result-text', 'game-over-text');
  ui.resultTitle = getByAnyId('game-over-title');
  ui.playAgainBtn = getByAnyId('play-again-btn');

  ensureMissingMounts();
}

function ensureMissingMounts() {
  if (!ui.aiHand && ui.aiBoard && ui.aiBoard.parentElement) {
    const aiHandWrap = document.createElement('div');
    aiHandWrap.id = 'ai-hand';
    aiHandWrap.className = 'hand-row';
    aiHandWrap.style.minHeight = '48px';
    aiHandWrap.style.marginBottom = '8px';
    ui.aiBoard.parentElement.insertBefore(aiHandWrap, ui.aiBoard);
    ui.aiHand = aiHandWrap;
  }

  if (!ui.message && ui.turnIndicator && ui.turnIndicator.parentElement) {
    const msg = document.createElement('div');
    msg.id = 'message';
    msg.style.minHeight = '1.2em';
    msg.style.color = '#f1c86b';
    ui.turnIndicator.parentElement.appendChild(msg);
    ui.message = msg;
  }
}

function cloneCard(card) {
  return {
    ...card,
    health: card.health,
    maxHealth: card.health,
    hasAttacked: false,
    divineShield: card.abilities.includes('divine_shield'),
    stealth: card.abilities.includes('stealth')
  };
}

function shuffle(array) {
  const arr = [...array];
  for (let i = arr.length - 1; i > 0; i -= 1) {
    const j = Math.floor(Math.random() * (i + 1));
    [arr[i], arr[j]] = [arr[j], arr[i]];
  }
  return arr;
}

function setMessage(text) {
  state.message = text;
  if (ui.message) {
    ui.message.textContent = text;
  }
}

function capHp() {
  state.playerHP = Math.max(0, Math.min(30, state.playerHP));
  state.aiHP = Math.max(0, Math.min(30, state.aiHP));
}

function drawCard(deckKey, handKey) {
  if (state[deckKey].length === 0) return;
  state[handKey].push(state[deckKey].shift());
}

function toggleScreen(screenEl, isActive) {
  if (!screenEl) return;
  screenEl.classList.toggle('active', isActive);
  screenEl.style.display = isActive ? 'block' : 'none';
}

function init() {
  setupUiReferences();

  toggleScreen(ui.gameScreen, false);
  toggleScreen(ui.gameOverScreen, false);
  toggleScreen(ui.classSelectScreen, true);

  if (ui.classList) {
    ui.classList.innerHTML = '';
    CLASS_NAMES.forEach((className) => {
      const btn = document.createElement('button');
      btn.type = 'button';
      btn.className = 'class-btn';
      btn.textContent = className[0].toUpperCase() + className.slice(1);
      btn.addEventListener('click', () => startGame(className));
      ui.classList.appendChild(btn);
    });
  }

  if (ui.playBtn) ui.playBtn.addEventListener('click', playCard);
  if (ui.attackBtn) ui.attackBtn.addEventListener('click', attack);
  if (ui.endTurnBtn) ui.endTurnBtn.addEventListener('click', endTurn);
  if (ui.playAgainBtn) ui.playAgainBtn.addEventListener('click', () => location.reload());

  setMessage('Pick a class to begin.');
}

function startGame(className) {
  const aiClassPool = CLASS_NAMES.filter((c) => c !== className);
  const aiClass = aiClassPool[Math.floor(Math.random() * aiClassPool.length)] || className;

  const playerDeck = shuffle(CARDS).slice(0, 10).map(cloneCard);
  const aiDeck = shuffle(CARDS).slice(0, 10).map(cloneCard);

  state = {
    playerHP: 30,
    aiHP: 30,
    playerMana: 3,
    aiMana: 3,
    maxMana: 3,
    playerHand: playerDeck.splice(0, 5),
    playerBoard: [],
    aiHand: aiDeck.splice(0, 5),
    aiBoard: [],
    playerDeck,
    aiDeck,
    turn: 'player',
    selectedCard: null,
    selectedBoardCard: null,
    gameOver: false,
    playerClass: className,
    aiClass,
    message: 'Battle started.'
  };

  toggleScreen(ui.classSelectScreen, false);
  toggleScreen(ui.gameOverScreen, false);
  toggleScreen(ui.gameScreen, true);

  render();
}

function renderCardElement(card, options = {}) {
  const el = document.createElement('div');
  el.className = 'card';
  if (options.small) el.classList.add('small');
  if (options.selected) el.classList.add('selected');
  if (card.hasAttacked) {
    el.classList.add('tapped');
    el.classList.add('exhausted');
  }
  if (card.abilities.includes('taunt')) el.classList.add('taunt');
  if (card.stealth) el.classList.add('stealth');

  const top = document.createElement('div');
  top.style.display = 'flex';
  top.style.justifyContent = 'space-between';

  const name = document.createElement('div');
  name.className = 'card-name';
  name.textContent = card.name;

  const cost = document.createElement('div');
  cost.className = 'card-line';
  cost.textContent = String(card.cost);

  top.appendChild(name);
  top.appendChild(cost);

  const typeLine = document.createElement('div');
  typeLine.className = 'card-line';
  typeLine.textContent = card.type === 'spell' ? `Spell (${card.class})` : card.class;

  const abilities = document.createElement('div');
  abilities.className = 'card-line';
  abilities.textContent = card.abilities.length ? card.abilities.join(', ') : 'No ability';

  const stats = document.createElement('div');
  stats.className = 'card-stats';
  stats.style.display = 'flex';
  stats.style.justifyContent = 'space-between';
  stats.style.marginTop = 'auto';

  const atk = document.createElement('span');
  atk.textContent = `ATK ${card.attack}`;

  const hp = document.createElement('span');
  hp.textContent = card.type === 'spell' ? '-' : `HP ${card.health}`;

  stats.appendChild(atk);
  stats.appendChild(hp);

  el.appendChild(top);
  el.appendChild(typeLine);
  el.appendChild(abilities);
  el.appendChild(stats);

  return el;
}

function renderFaceDownCard() {
  const el = document.createElement('div');
  el.className = 'card small';
  el.style.display = 'flex';
  el.style.alignItems = 'center';
  el.style.justifyContent = 'center';
  el.textContent = 'Card';
  return el;
}

function render() {
  capHp();

  if (ui.aiHP) ui.aiHP.textContent = `${state.aiHP} / 30`;
  if (ui.playerHP) ui.playerHP.textContent = `${state.playerHP} / 30`;

  if (ui.aiHPFill) ui.aiHPFill.style.width = `${(state.aiHP / 30) * 100}%`;
  if (ui.playerHPFill) ui.playerHPFill.style.width = `${(state.playerHP / 30) * 100}%`;

  if (ui.aiHand) {
    ui.aiHand.innerHTML = '';
    for (let i = 0; i < state.aiHand.length; i += 1) {
      ui.aiHand.appendChild(renderFaceDownCard());
    }
  }

  if (ui.aiBoard) {
    ui.aiBoard.innerHTML = '';
    state.aiBoard.forEach((card) => {
      const cardEl = renderCardElement(card, { small: true });
      ui.aiBoard.appendChild(cardEl);
    });
  }

  if (ui.playerBoard) {
    ui.playerBoard.innerHTML = '';
    state.playerBoard.forEach((card, index) => {
      const cardEl = renderCardElement(card, {
        small: true,
        selected: state.selectedBoardCard === index
      });
      cardEl.addEventListener('click', () => {
        if (state.turn !== 'player' || state.gameOver) return;
        state.selectedBoardCard = state.selectedBoardCard === index ? null : index;
        render();
      });
      ui.playerBoard.appendChild(cardEl);
    });
  }

  if (ui.hand) {
    ui.hand.innerHTML = '';
    state.playerHand.forEach((card, index) => {
      const cardEl = renderCardElement(card, { selected: state.selectedCard === index });
      cardEl.addEventListener('click', () => {
        if (state.turn !== 'player' || state.gameOver) return;
        state.selectedCard = state.selectedCard === index ? null : index;
        render();
      });
      ui.hand.appendChild(cardEl);
    });
  }

  if (ui.manaDisplay) ui.manaDisplay.textContent = `Mana: ${state.playerMana}/${state.maxMana}`;

  if (ui.turnIndicator) {
    const isPlayerTurn = state.turn === 'player';
    ui.turnIndicator.textContent = isPlayerTurn ? 'YOUR TURN' : 'AI TURN';
    ui.turnIndicator.style.color = isPlayerTurn ? '#40c970' : '#9ca3af';
    ui.turnIndicator.classList.toggle('your-turn', isPlayerTurn);
    ui.turnIndicator.classList.toggle('ai-turn', !isPlayerTurn);
  }

  if (ui.classVs && state.playerClass && state.aiClass) {
    ui.classVs.textContent = `${capitalize(state.playerClass)} vs ${capitalize(state.aiClass)}`;
  }

  if (ui.message) ui.message.textContent = state.message || '';

  const playerActive = state.turn === 'player' && !state.gameOver;
  if (ui.playBtn) ui.playBtn.style.display = playerActive ? 'inline-block' : 'none';
  if (ui.attackBtn) ui.attackBtn.style.display = playerActive ? 'inline-block' : 'none';
  if (ui.endTurnBtn) ui.endTurnBtn.style.display = playerActive ? 'inline-block' : 'none';

  if (ui.playBtn) ui.playBtn.disabled = !playerActive;
  if (ui.attackBtn) ui.attackBtn.disabled = !playerActive;
  if (ui.endTurnBtn) ui.endTurnBtn.disabled = !playerActive;

  checkWin();
}

function capitalize(value) {
  return value[0].toUpperCase() + value.slice(1);
}

function applySpell(card, isPlayer) {
  if (card.id === 'wind-trap') {
    state.aiHP -= 3;
    setMessage('Wind Trap deals 3 damage to AI.');
    return;
  }

  if (card.id === 'soul-drain') {
    state.aiHP -= 3;
    state.playerHP += 3;
    setMessage('Soul Drain steals 3 HP.');
    return;
  }

  if (card.id === 'healing-bloom') {
    state.playerHP += 4;
    setMessage('Healing Bloom restores 4 HP.');
    return;
  }

  if (card.id === 'smoke-bomb') {
    const board = isPlayer ? state.playerBoard : state.aiBoard;
    board.forEach((minion) => {
      minion.stealth = true;
    });
    setMessage('Smoke Bomb grants stealth to all allies.');
    return;
  }

  if (card.id === 'overclock') {
    state.aiHP -= 4;
    setMessage('Overclock deals 4 damage to AI.');
  }
}

function playCard() {
  if (state.turn !== 'player' || state.gameOver) return;

  if (state.selectedCard === null) {
    setMessage('Select a card first');
    render();
    return;
  }

  const card = state.playerHand[state.selectedCard];
  if (!card) {
    setMessage('Invalid card selection');
    state.selectedCard = null;
    render();
    return;
  }

  if (card.cost > state.playerMana) {
    setMessage('Not enough mana');
    render();
    return;
  }

  state.playerMana -= card.cost;
  state.playerHand.splice(state.selectedCard, 1);

  if (card.type === 'spell') {
    applySpell(card, true);
  } else {
    state.playerBoard.push(card);
    setMessage(`Played ${card.name}.`);
  }

  state.selectedCard = null;
  checkWin();
  render();
}

function findFirstVisibleTarget(board) {
  return board.find((card) => !card.stealth) || null;
}

function applyDamage(target, amount) {
  if (amount <= 0) return;
  if (target.divineShield) {
    target.divineShield = false;
    return;
  }
  target.health -= amount;
}

function combat(attacker, defender, isPlayerAttacker) {
  applyDamage(defender, attacker.attack);
  applyDamage(attacker, defender.attack);

  if (attacker.abilities.includes('lifesteal')) {
    if (isPlayerAttacker) {
      state.playerHP += attacker.attack;
    } else {
      state.aiHP += attacker.attack;
    }
  }

  if (defender.abilities.includes('lifesteal')) {
    if (isPlayerAttacker) {
      state.aiHP += defender.attack;
    } else {
      state.playerHP += defender.attack;
    }
  }

  state.playerBoard = state.playerBoard.filter((card) => card.health > 0);
  state.aiBoard = state.aiBoard.filter((card) => card.health > 0);
}

function attack() {
  if (state.turn !== 'player' || state.gameOver) return;

  if (state.selectedBoardCard === null) {
    setMessage('Select a minion to attack with');
    render();
    return;
  }

  const attacker = state.playerBoard[state.selectedBoardCard];
  if (!attacker) {
    setMessage('Invalid attacker');
    state.selectedBoardCard = null;
    render();
    return;
  }

  if (attacker.hasAttacked) {
    setMessage('Already attacked this turn');
    render();
    return;
  }

  const target = findFirstVisibleTarget(state.aiBoard);

  if (target) {
    combat(attacker, target, true);
    setMessage(`${attacker.name} attacks ${target.name}.`);
  } else {
    state.aiHP -= attacker.attack;
    if (attacker.abilities.includes('lifesteal')) {
      state.playerHP += attacker.attack;
    }
    setMessage(`${attacker.name} hits AI for ${attacker.attack}.`);
  }

  if (attacker.stealth) attacker.stealth = false;
  attacker.hasAttacked = true;
  state.selectedBoardCard = null;

  checkWin();
  render();
}

function endTurn() {
  if (state.turn !== 'player' || state.gameOver) return;

  state.playerBoard.forEach((card) => {
    card.hasAttacked = false;
  });
  state.turn = 'ai';
  setMessage('AI is thinking...');
  render();

  setTimeout(aiTurn, 800);
}

function aiPlayAffordableCards() {
  let played = true;
  while (played) {
    played = false;
    const idx = state.aiHand.findIndex((card) => card.cost <= state.aiMana);
    if (idx === -1) break;

    const card = state.aiHand[idx];
    state.aiMana -= card.cost;
    state.aiHand.splice(idx, 1);

    if (card.type === 'spell') {
      aiCastSpell(card);
    } else {
      state.aiBoard.push(card);
    }

    played = true;
  }
}

function aiCastSpell(card) {
  if (card.id === 'wind-trap') {
    state.playerHP -= 3;
    return;
  }

  if (card.id === 'soul-drain') {
    state.playerHP -= 3;
    state.aiHP += 3;
    return;
  }

  if (card.id === 'healing-bloom') {
    state.aiHP += 4;
    return;
  }

  if (card.id === 'smoke-bomb') {
    state.aiBoard.forEach((minion) => {
      minion.stealth = true;
    });
    return;
  }

  if (card.id === 'overclock') {
    state.playerHP -= 4;
  }
}

function aiAttackWithBoard() {
  for (const attacker of state.aiBoard) {
    if (state.gameOver) return;
    const target = findFirstVisibleTarget(state.playerBoard);

    if (target) {
      combat(attacker, target, false);
    } else {
      state.playerHP -= attacker.attack;
      if (attacker.abilities.includes('lifesteal')) {
        state.aiHP += attacker.attack;
      }
    }

    if (attacker.stealth) attacker.stealth = false;
  }
}

function aiTurn() {
  if (state.gameOver) return;

  state.aiMana = Math.min(state.aiMana + 1, 10);
  state.maxMana = Math.min(state.maxMana + 1, 10);

  drawCard('aiDeck', 'aiHand');
  aiPlayAffordableCards();
  aiAttackWithBoard();

  checkWin();
  if (state.gameOver) {
    render();
    return;
  }

  state.turn = 'player';
  state.playerMana = 3;
  drawCard('playerDeck', 'playerHand');
  setMessage('Your turn.');

  render();
}

function checkWin() {
  capHp();
  if (state.aiHP <= 0) {
    playerWins();
    return true;
  }
  if (state.playerHP <= 0) {
    playerLoses();
    return true;
  }
  return false;
}

function playerWins() {
  state.gameOver = true;
  if (ui.resultTitle) ui.resultTitle.textContent = 'Victory';
  if (ui.resultText) ui.resultText.textContent = 'You won the brawl!';
  toggleScreen(ui.gameScreen, false);
  toggleScreen(ui.gameOverScreen, true);
}

function playerLoses() {
  state.gameOver = true;
  if (ui.resultTitle) ui.resultTitle.textContent = 'Defeat';
  if (ui.resultText) ui.resultText.textContent = 'The AI won this brawl.';
  toggleScreen(ui.gameScreen, false);
  toggleScreen(ui.gameOverScreen, true);
}

init();
