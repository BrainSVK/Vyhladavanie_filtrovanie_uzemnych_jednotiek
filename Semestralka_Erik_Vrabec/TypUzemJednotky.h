#pragma once
enum class TypUzemJednotky {STAT, KRAJ, OKRES, OBEC};

enum class TypVzdelania {BEZ_UKONCENIA_VZDELANIA, ZAKLADNE, UCNOVSKE, STREDNE, VYSSIE, VYSOKOSKOLSKE, BEZ_VZDELANIA, NEZISTENE};

inline const char* ToString(int i)
{
    switch (i)
    {
    case 0: return "BEZ_UKONCENIA_VZDELANIA";
    case 1: return "ZAKLADNE";
    case 2: return "UCNOVSKE";
    case 3: return "STREDNE";
    case 4: return "VYSSIE";
    case 5: return "VYSOKOSKOLSKE";
    case 6: return "BEZ_VZDELANIA";
    case 7 : return "NEZISTENE";
    default: return "";
    }
}