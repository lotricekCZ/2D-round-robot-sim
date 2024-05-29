# Introduction
Toto je implementace ICP projektu a simulátoru mobilních robotů. ode mne, xramas01.
# Sestavení
K sestavení je nezbytný CMake, který je zavolán uvnitř unix makefile:
```bash
make run
```
# Běh
Spustitelný soubor lze poté nalézt v ./build složce pod názvem `simulator` a nepotřebuje žádné argumenty, nebo klasisky make run.
# Uživatelské prostředí
Uživatelské prostředí bylo něco, u čeho jsem spoléhal na kolegu, který mi bohužel v sobotu oznámil, že je toho na něj moc.
Na herní plochu je nezbytné nejdříve nakliknout, aby na ní bylo zaměřeno.
V levé straně okna je menu, list elementů mimo hráče a i možnost upravovat atributy vybraného elementu, v druhé záložce jsou poté objekty, které lze přidat na prostředí.
K vizualizaci prostředí jsem se rozhodl pro použití OpenGLWidgetu, respektive jeho derivátu.
## Testy
Lze je zavolat s pomocí `make test`, nicméně testují především funkčnost implementace geometrické knihovny.