"""Génère projects.json à partir de l'en-tête (front matter) de chaque readme.md.

Utilisation, depuis la racine du dépôt :
    python3 tools/build_index.py

À relancer après chaque ajout ou modification d'un projet.
Aucune bibliothèque à installer (Python 3 standard).
"""
import json
import pathlib

ROOT = pathlib.Path(__file__).resolve().parent.parent
RAW = "https://raw.githubusercontent.com/zakariarhiba/ARDUINO-PROJECTS/main"


def parse_front_matter(text):
    """Lit le bloc entre les deux lignes '---' au début du fichier."""
    if not text.startswith("---"):
        return None, text
    _, block, body = text.split("---", 2)
    data, current_list = {}, None
    for line in block.strip("\n").splitlines():
        if not line.strip():
            continue
        if line.startswith("  - ") or line.startswith("    "):
            key, value = line.strip().lstrip("- ").split(":", 1)
            if line.startswith("  - "):
                current_list.append({})
            current_list[-1][key.strip()] = json.loads(value.strip())
            continue
        key, value = line.split(":", 1)
        value = value.strip()
        if value == "":
            data[key] = current_list = []
        else:
            data[key] = json.loads(value)
    return data, body.lstrip("\n")


def main():
    projects = []
    for readme in sorted(ROOT.glob("*/readme.md")):
        meta, _ = parse_front_matter(readme.read_text(encoding="utf-8"))
        if not meta:
            continue
        folder = readme.parent.name
        meta["folder"] = folder
        meta["readme"] = f"{RAW}/{folder}/readme.md"
        projects.append(meta)
    projects.sort(key=lambda p: p.get("order", 999))
    out = ROOT / "projects.json"
    out.write_text(json.dumps({"projects": projects}, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(f"{len(projects)} projets écrits dans {out.name}")


if __name__ == "__main__":
    main()
