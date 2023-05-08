#pragma once

#include "utils/types.hpp"

/// Taken from https://github.com/ProgramEngineeringKPI/Introduction-To-Programming/blob/master/labs_spring_2021/assignment_4.md
// With additional details from https://web.archive.org/web/20080912171714/http://www.fortunecity.com/skyscraper/windows/364/bmpffrmt.html

constexpr int Channels = 3;
constexpr int RowAlignment = 4;

// C++ makes gaps between types to align them, remove gaps to match bmp layout!
#pragma pack(push, 1)
struct BMPHeader{
     s8 id[2] = {'B', 'M'};            // Завжди дві літери 'B' і 'M'
     s32 filesize = 0;        // Розмір файла в байтах
     s16 reserved[2] = {0, 0};// 0, 0
     s32 headersize = 54;     // 54L для 24-бітних зображень
     s32 infoSize = 40;       // 40L для 24-бітних зображень
     s32 width = 0;           // ширина зображення в пікселях
     s32 depth = 0;           // висота зображення в пікселях
     s16 biPlanes = 1;        // 1 (для 24-бітних зображень)
     s16 bits = 24;           // 24 (для 24-бітних зображень)
     s32 biCompression = 0;   // 0L
     s32 biSizeImage = 0;     // Можна поставити в 0L для зображень без компрессії (наш варіант)
     s32 biXPelsPerMeter = 0; // Рекомендована кількість пікселів на метр, можна 0L
     s32 biYPelsPerMeter = 0; // Те саме, по висоті
     s32 biClrUsed = 0;       // Для індексованих зображень, можна поставити 0L
     s32 biClrImportant = 0;  // Те саме
};
#pragma pack(pop)
