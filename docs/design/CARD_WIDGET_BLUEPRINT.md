# BP_CardWidget Setup Guide (UE5.7)

This guide creates a `BP_CardWidget` blueprint based on `UCardWidget` and wires it to the C++ `BindWidget` fields.

## 1) Create the Blueprint

1. In Unreal Editor 5.7, open the Content Browser.
2. Click `Add` -> `Blueprint Class`.
3. Click `All Classes`, search for `CardWidget`.
4. Select parent class `UCardWidget`.
5. Name it `BP_CardWidget` and open it.

## 2) Build the Designer Layout

1. In the `Designer` tab, keep/add a `Canvas Panel` as the root.
2. Add an `Image` for the border:
- Rename to `CardBorder`
- Set size to `300 x 420`
- Anchor center (or top-left if your HUD handles placement)
3. Add an `Image` for the portrait art:
- Rename to `CardArt`
- Set size to `240 x 300`
- Place centered inside the border area
4. Add an `Image` for card back:
- Rename to `CardBack`
- Set size to `240 x 300` (same as `CardArt`)
- Place at the same position as `CardArt`
- Set Visibility to `Hidden`
5. Add `TextBlock` widgets and rename exactly:
- `CardNameText`
- `CardCostText`
- `CardAttackText`
- `CardHealthText`
- `CardDescriptionText`

## 3) Bind to C++ `BindWidget` Fields

In the `Hierarchy`, names must match the C++ properties exactly:

- `CardArt` -> `UImage* CardArt`
- `CardBack` -> `UImage* CardBack`
- `CardNameText` -> `UTextBlock* CardNameText`
- `CardCostText` -> `UTextBlock* CardCostText`
- `CardAttackText` -> `UTextBlock* CardAttackText`
- `CardHealthText` -> `UTextBlock* CardHealthText`
- `CardDescriptionText` -> `UTextBlock* CardDescriptionText`

For card frame styling, keep `CardFrame` bound if your widget uses a `Border` named `CardFrame`.

## 4) Graph Wiring

In the `Graph` tab for `BP_CardWidget`:

1. Add `Event BeginPlay`.
2. Add your card lookup node chain (`Get Card Data` from your game system).
3. Set `CardPortraitTexture` using a soft texture reference from that card data.
4. Call `LoadTextures`.
5. Call `ShowFaceUp`.

Flow:

`BeginPlay` -> `Get Card Data` -> `Set CardPortraitTexture` -> `LoadTextures` -> `ShowFaceUp`

## 5) Set `CardPortraitTexture` as Soft Reference

`CardPortraitTexture` is a `TSoftObjectPtr<UTexture2D>`.

Options:

1. In Defaults for `BP_CardWidget`, set `CardPortraitTexture` to a texture asset picker value.
2. At runtime, set it from a string path converted to soft object reference.

Expected portrait path pattern:

`/Game/EndlessModularTCGTradingCardCollection/Artwork/<ClassFolder>/<CardId>`

Example:

`/Game/EndlessModularTCGTradingCardCollection/Artwork/Warriors/warrior-the-iron-oath`

After setting the soft reference, call `LoadTextures` so `CardArt` updates.
