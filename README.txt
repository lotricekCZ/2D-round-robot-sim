# Introduction
Toto je implementace ICP projektu a simulátoru mobilních robotů. ode mne, xramas01.
# Sestavení
K sestavení je nezbytný CMake, který je zavolán následující sekvencí:
```bash
mkdir build && cd build && cmake .. && make -j`nproc`
```
# Běh
Spustitelný soubor lze poté nalézt v ./build složce pod názvem `simulator` a nepotřebuje žádné argumenty.
# Uživatelské prostředí
Uživatelské prostředí bylo něco, u čeho jsem spoléhal na kolegu, který mi bohužel v sobotu oznámil, že je toho na něj moc.
Na herní plochu je nezbytné nejdříve nakliknout, aby na ní bylo zaměřeno.
V levé straně okna je menu, list elementů mimo hráče a i možnost upravovat atributy vybraného elementu, v druhé záložce jsou poté objekty, které lze přidat na prostředí.
K vizualizaci prostředí jsem se rozhodl pro použití OpenGLWidgetu, respektive jeho derivátu.
## Testy
Lze je zavolat s pomocí `make test`, nicméně testují především funkčnost implementace geometrické knihovny.
## Dodatek
Sám moc nejsem spokojen s výsledkem v tom smyslu, že bych s více časem plněji využil možnosti mé knihovny tvarů a dodal projektu řádný diagram a rozsáhlejší dokumentaci.