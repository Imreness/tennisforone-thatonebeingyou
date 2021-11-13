# Tennis For One - That One Being You
- [Tennis For One - That One Being You](#tennis-for-one---that-one-being-you)
- [Overview](#overview)
- [Engine Design](#engine-design)
- [Development flow](#development-flow)
- [Lessons Learned](#lessons-learned)

# Overview

The Game was made as a *programming* exercise, which is the the primary reason for the lacking asset and game design quality. Even though the artstyle is supposed to mimmick late 90's early 3D games, It doesnt really come through.

# Engine Design
The engine is a finite-state machine. Each game state has its own variable, which are cleared upon state-switching. Within these variables, the game handles internal logic, Rendering, Physics, Audio, etc.

Internal logic are in object's process functions OR in the state's process functions.

# Development flow
Assets and levels are created in an external 3D modelling tool, from which a .DAE file is exported. The asset packer loads these .DAE files then packs it into .assetbundle files, which are loaded by the game by itself.

Game Logic, since there isn't a dedicated editor, is written into the engine itself via c++.

# Lessons Learned
An editor is a must. Even in this simple game an editor would've saved a ton of time. (All the while, the actual development of the editor would eat a lof ot time too, editor only needs to be written once... probably once.)