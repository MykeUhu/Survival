# UhuGameplayTags.h & .cpp

# UhuSurvivalGame ToDo List

## Bug Fixes

- [ ] Initialize FCraftingRecipe::ResultQuantity in UhuCraftingComponent.h
- [ ] Initialize FInventoryItem::Quantity in UhuInventoryComponent.h
- [ ] Initialize FInventoryItem::Weight in UhuInventoryComponent.h
- [ ] Initialize FMovementSpeedLevel::Speed in UhuMovementDataAsset.h
- [ ] Initialize FMovementSpeedLevel::StaminaCost in UhuMovementDataAsset.h
- [ ] Initialize FSkillLevelData::Level in UhuSkillLevelingComponent.h
- [ ] Initialize FSkillLevelData::Experience in UhuSkillLevelingComponent.h
- [ ] Initialize FSkillLevelData::ExperienceRequiredForNextLevel in UhuSkillLevelingComponent.h

## Blueprint Implementation

### Character Blueprint

- [ ] Create a Blueprint class based on AUhuSurvivalCharacter
- [ ] Set up character mesh and animations
- [ ] Implement character movement input
- [ ] Create UI for displaying character stats (Health, Stamina, Hunger, Thirst)
- [ ] Implement the emote wheel UI
- [ ] Set up character inventory UI

### Gameplay Systems

- [ ] Create Blueprint implementation of the inventory system
- [ ] Implement crafting system UI and functionality
- [ ] Set up interaction system for objects in the world
- [ ] Implement day/night cycle visualization
- [ ] Create UI for skill leveling and progression

### Movement System

- [ ] Implement speed adjustment using mouse wheel in Blueprint
- [ ] Create visual feedback for current movement speed
- [ ] Set up stamina consumption based on movement speed

### Drone AI

- [ ] Create Blueprint for drone behavior
- [ ] Implement drone commands (Sleep, Gather, Build, Scan)
- [ ] Set up drone inventory and resource gathering

### Environment

- [ ] Create basic level layout
- [ ] Implement resource nodes for gathering
- [ ] Set up weather system (if planned)

### UI/UX

- [ ] Design and implement main menu
- [ ] Create HUD elements for player stats
- [ ] Implement pause menu
- [ ] Design and create inventory UI
- [ ] Implement crafting menu

## Project Roadmap

### Phase 1: Core Mechanics (Current)

- [ ] Fix all initialization bugs
- [ ] Implement basic character movement and controls
- [ ] Set up inventory and crafting systems
- [ ] Implement skill leveling system
- [ ] Create basic environment with resource gathering

### Phase 2: AI and Advanced Features

- [ ] Develop drone AI and commands
- [ ] Implement advanced crafting recipes
- [ ] Create more complex environments
- [ ] Add basic enemy AI (if planned)

### Phase 3: Polish and Optimization

- [ ] Refine UI/UX
- [ ] Optimize performance
- [ ] Add sound effects and music
- [ ] Implement save/load system

### Phase 4: Testing and Feedback

- [ ] Conduct internal playtesting
- [ ] Fix bugs and issues found during testing
- [ ] Implement feedback from testers

### Phase 5: Pre-release

- [ ] Finalize all features
- [ ] Polish graphics and animations
- [ ] Prepare marketing materials
- [ ] Set up distribution platform (Steam, Epic Games Store, etc.)

### Phase 6: Release and Post-launch

- [ ] Release demo version for public testing
- [ ] Gather and analyze player feedback
- [ ] Plan post-launch content and updates

## Notes

- Prioritize fixing the initialization bugs as they may cause stability issues.
- Focus on implementing core gameplay mechanics before moving on to advanced features.
- Regularly playtest the game to ensure a smooth and enjoyable experience.
- Keep documentation updated as you progress through the project.

#### **Legende**
✅ **_Erledigt_**  
❌ **_Fehlt_**  
❓ **_Unklar_**  
✨ **_Überprüfen_**  
🔴 **_Wichtig_**   
-[ ] **_Offen_**
