# Manual test plan

- [ ] Clean CMake configure/build on Windows
- [ ] Game starts with two rows of animated enemies
- [ ] WASD / arrow movement respects window boundaries
- [ ] Space fires one bullet; bullets move upward
- [ ] Bullet-enemy contact removes both and increases score by 10
- [ ] Enemy touching player removes one life; temporary invulnerability prevents rapid loss
- [ ] Clearing wave 1 starts wave 2
- [ ] Clearing wave 2 displays YOU WIN in window title
- [ ] Losing all lives displays GAME OVER in window title
- [ ] R restarts and resets score/lives/wave
- [ ] N and M developer controls do not crash when no enemies remain
- [ ] Esc closes the game
- [ ] Assets load correctly when running from the executable directory

This environment did not include SDL2 development headers/libraries during packaging. The Windows build and runtime tests must be completed locally.
