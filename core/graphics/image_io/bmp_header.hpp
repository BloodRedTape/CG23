#pragma once

#include "utils/types.hpp"

/// Taken from https://github.com/ProgramEngineeringKPI/Introduction-To-Programming/blob/master/labs_spring_2021/assignment_4.md
// With additional details from https://web.archive.org/web/20080912171714/http://www.fortunecity.com/skyscraper/windows/364/bmpffrmt.html

constexpr int Channels = 3;
constexpr int RowAlignment = 4;

// C++ makes gaps between types to align them, remove gaps to match bmp layout!
#pragma pack(push, 1)
struct BMPHeader{
     s8 id[2] = {'B', 'M'};            // ������ �� ����� 'B' � 'M'
     s32 filesize = 0;        // ����� ����� � ������
     s16 reserved[2] = {0, 0};// 0, 0
     s32 headersize = 54;     // 54L ��� 24-����� ���������
     s32 infoSize = 40;       // 40L ��� 24-����� ���������
     s32 width = 0;           // ������ ���������� � �������
     s32 depth = 0;           // ������ ���������� � �������
     s16 biPlanes = 1;        // 1 (��� 24-����� ���������)
     s16 bits = 24;           // 24 (��� 24-����� ���������)
     s32 biCompression = 0;   // 0L
     s32 biSizeImage = 0;     // ����� ��������� � 0L ��� ��������� ��� �������� (��� ������)
     s32 biXPelsPerMeter = 0; // ������������� ������� ������ �� ����, ����� 0L
     s32 biYPelsPerMeter = 0; // �� ����, �� �����
     s32 biClrUsed = 0;       // ��� ������������ ���������, ����� ��������� 0L
     s32 biClrImportant = 0;  // �� ����
};
#pragma pack(pop)
