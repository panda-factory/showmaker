//
// Created by guozhenxiong on 2021-10-10.
//

#ifndef STRUGGLE_COLOR_H
#define STRUGGLE_COLOR_H

#include <cmath>
#include <cstdint>

namespace strg {
namespace css {
class Color {
public:
    explicit constexpr Color(std::uint32_t argb)
    : red_{static_cast<std::uint8_t>(argb >> 24)}
    , green_{static_cast<std::uint8_t>(argb >> 16)}
    , blue_{static_cast<std::uint8_t>(argb >> 8)}
    , alpha_{static_cast<std::uint8_t>(argb)}
    {}

private:
    std::uint8_t red_;
    std::uint8_t green_;
    std::uint8_t blue_;
    std::uint8_t alpha_;
};

namespace colors {

#ifdef TRANSPARENT
#undef TRANSPARENT
#endif // TRANSPARENT
static constexpr Color TRANSPARENT             {0x00000000};

static constexpr Color ALICE_BLUE              {0xF0F8FFFF};
static constexpr Color ANTIQUE_WHITE           {0xFAEBD7FF};
static constexpr Color AQUA                    {0X00FFFFFF};
static constexpr Color AQUAMARINE              {0X7FFFD4FF};
static constexpr Color AZURE                   {0xF0FFFFFF};
static constexpr Color BEIGE                   {0xF5F5DCFF};
static constexpr Color BISQUE                  {0xFFE4C4FF};
static constexpr Color BLACK                   {0x000000FF};
static constexpr Color BLANCHED_ALMOND         {0xFFEBCDFF};
static constexpr Color BLUE                    {0x0000FFFF};
static constexpr Color BLUE_VIOLET             {0x8A2BE2FF};
static constexpr Color BROWN                   {0xA52A2AFF};
static constexpr Color BURLY_WOOD              {0xDEB887FF};
static constexpr Color CADET_BLUE              {0x5F9EA0FF};
static constexpr Color CHARTREUSE              {0x7FFF00FF};
static constexpr Color CHOCOLATE               {0xD2691EFF};
static constexpr Color CORAL                   {0xFF7F50FF};
static constexpr Color CORNFLOWER_BLUE         {0x6495EDFF};
static constexpr Color CORNSILK                {0xFFF8DCFF};
static constexpr Color CRIMSON                 {0xDC143CFF};
static constexpr Color CYAN                    {0x00FFFFFF};
static constexpr Color DARK_BLUE               {0x00008BFF};
static constexpr Color DARK_CYAN               {0x008B8BFF};
static constexpr Color DARK_GOLDEN_ROD         {0xB8860BFF};
static constexpr Color DARK_GRAY               {0xA9A9A9FF};
static constexpr Color DARK_GREY               {0xA9A9A9FF};
static constexpr Color DARK_GREEN              {0x006400FF};
static constexpr Color DARK_KHAKI              {0xBDB76BFF};
static constexpr Color DARK_MAGENTA            {0x8B008BFF};
static constexpr Color DARK_OLIVE_GREEN        {0x556B2FFF};
static constexpr Color DARK_ORANGE             {0xFF8C00FF};
static constexpr Color DARK_ORCHID             {0x9932CCFF};
static constexpr Color DARK_RED                {0x8B0000FF};
static constexpr Color DARK_SALMON             {0xE9967AFF};
static constexpr Color DARK_SEA_GREEN          {0x8FBC8FFF};
static constexpr Color DARK_SLATE_BLUE         {0x483D8BFF};
static constexpr Color DARK_SLATE_GRAY         {0x2F4F4FFF};
static constexpr Color DARK_SLATE_GREY         {0x2F4F4FFF};
static constexpr Color DARK_TURQUOISE          {0x00CED1FF};
static constexpr Color DARK_VIOLET             {0x9400D3FF};
static constexpr Color DEEP_PINK               {0xFF1493FF};
static constexpr Color DEEP_SKY_BLUE           {0x00BFFFFF};
static constexpr Color DIM_GRAY                {0x696969FF};
static constexpr Color DIM_GREY                {0x696969FF};
static constexpr Color DODGER_BLUE             {0x1E90FFFF};
static constexpr Color FIRE_BRICK              {0xB22222FF};
static constexpr Color FLORAL_WHITE            {0xFFFAF0FF};
static constexpr Color FOREST_GREEN            {0x228B22FF};
static constexpr Color FUCHSIA                 {0xFF00FFFF};
static constexpr Color GAINSBORO               {0xDCDCDCFF};
static constexpr Color GHOST_WHITE             {0xF8F8FFFF};
static constexpr Color GOLD                    {0xFFD700FF};
static constexpr Color GOLDEN_ROD              {0xDAA520FF};
static constexpr Color GRAY                    {0x808080FF};
static constexpr Color GREY                    {0x808080FF};
static constexpr Color GREEN                   {0x008000FF};
static constexpr Color GREEN_YELLOW            {0xADFF2FFF};
static constexpr Color HONEY_DEW               {0xF0FFF0FF};
static constexpr Color HOT_PINK                {0xFF69B4FF};
static constexpr Color INDIAN_RED              {0xCD5C5CFF};
static constexpr Color INDIGO                  {0x4B0082FF};
static constexpr Color IVORY                   {0xFFFFF0FF};
static constexpr Color KHAKI                   {0xF0E68CFF};
static constexpr Color LAVENDER                {0xE6E6FAFF};
static constexpr Color LAVENDER_BLUSH          {0xFFF0F5FF};
static constexpr Color LAWN_GREEN              {0x7CFC00FF};
static constexpr Color LEMON_CHIFFON           {0xFFFACDFF};
static constexpr Color LIGHT_BLUE              {0xADD8E6FF};
static constexpr Color LIGHT_CORAL             {0xF08080FF};
static constexpr Color LIGHT_CYAN              {0xE0FFFFFF};
static constexpr Color LIGHT_GOLDEN_ROD_YELLOW {0xFAFAD2FF};
static constexpr Color LIGHT_GRAY              {0xD3D3D3FF};
static constexpr Color LIGHT_GREY              {0xD3D3D3FF};
static constexpr Color LIGHT_GREEN             {0x90EE90FF};
static constexpr Color LIGHT_PINK              {0xFFB6C1FF};
static constexpr Color LIGHT_SALMON            {0xFFA07AFF};
static constexpr Color LIGHT_SEA_GREEN         {0x20B2AAFF};
static constexpr Color LIGHT_SKY_BLUE          {0x87CEFAFF};
static constexpr Color LIGHT_SLATE_GRAY        {0x778899FF};
static constexpr Color LIGHT_SLATE_GREY        {0x778899FF};
static constexpr Color LIGHT_STEEL_BLUE        {0xB0C4DEFF};
static constexpr Color LIGHT_YELLOW            {0xFFFFE0FF};
static constexpr Color LIME                    {0x00FF00FF};
static constexpr Color LIME_GREEN              {0x32CD32FF};
static constexpr Color LINEN                   {0xFAF0E6FF};
static constexpr Color MAGENTA                 {0xFF00FFFF};
static constexpr Color MAROON                  {0x800000FF};
static constexpr Color MEDIUM_AQUA_MARINE      {0x66CDAAFF};
static constexpr Color MEDIUM_BLUE             {0x0000CDFF};
static constexpr Color MEDIUM_ORCHID           {0XBA55D3FF};
static constexpr Color MEDIUM_PURPLE           {0x9370DBFF};
static constexpr Color MEDIUM_SEA_GREEN        {0x3CB371FF};
static constexpr Color MEDIUM_SLATE_BLUE       {0x7B68EEFF};
static constexpr Color MEDIUM_SPRING_GREEN     {0x00FA9AFF};
static constexpr Color MEDIUM_TURQOISE         {0x48D1CCFF};
static constexpr Color MEDIUM_VIOLET_RED       {0xC71585FF};
static constexpr Color MIDNIGHT_BLUE           {0x191970FF};
static constexpr Color MINT_CREAM              {0xF5FFFAFF};
static constexpr Color MISTY_ROSE              {0xFFE4E1FF};
static constexpr Color MOCCASIN                {0xFFE4B5FF};
static constexpr Color NAVAJO_WHITE            {0xFFDEADFF};
static constexpr Color NAVY                    {0x000080FF};
static constexpr Color OLD_LACE                {0xFDF5E6FF};
static constexpr Color OLIVE                   {0x808000FF};
static constexpr Color OLIVE_DRAB              {0x6B8E23FF};
static constexpr Color ORANGE                  {0xFFA500FF};
static constexpr Color ORANGE_RED              {0xFF4500FF};
static constexpr Color ORCHID                  {0xDA70D6FF};
static constexpr Color PALE_GOLDEN_ROD         {0xEEE8AAFF};
static constexpr Color PALE_GREEN              {0x98FB98FF};
static constexpr Color PALE_TURQUOISE          {0xAFEEEEFF};
static constexpr Color PALE_VIOLET_RED         {0xDB7093FF};
static constexpr Color PAPAYA_WHIP             {0xFFEFD5FF};
static constexpr Color PEACH_PUFF              {0xFFC0CBFF};
static constexpr Color PERU                    {0xCD853FFF};
static constexpr Color PINK                    {0xFFC0CBFF};
static constexpr Color PLUM                    {0xDDA0DDFF};
static constexpr Color POWDER_BLUE             {0xB0E0E6FF};
static constexpr Color PURPLE                  {0x800080FF};
static constexpr Color REBECCA_PURPLE          {0x663399FF};
static constexpr Color RED                     {0xFF0000FF};
static constexpr Color ROSY_BROWN              {0xBC8F8FFF};
static constexpr Color ROYAL_BLUE              {0x4169E1FF};
static constexpr Color SADDLE_BROWN            {0x8B4513FF};
static constexpr Color SALMON                  {0xFA8072FF};
static constexpr Color SANDY_BROWN             {0xF4A460FF};
static constexpr Color SEA_GREEN               {0x2E8B57FF};
static constexpr Color SEA_SHELL               {0xFFF5EEFF};
static constexpr Color SIENNA                  {0xA0522DFF};
static constexpr Color SILVER                  {0xC0C0C0FF};
static constexpr Color SKY_BLUE                {0x87CEEBFF};
static constexpr Color SLATE_BLUE              {0x6A5ACDFF};
static constexpr Color SLATE_GRAY              {0x708090FF};
static constexpr Color SLATE_GREY              {0x708090FF};
static constexpr Color SNOW                    {0xFFFAFAFF};
static constexpr Color SPRING_GREEN            {0x00FF7FFF};
static constexpr Color STEEL_BLUE              {0x4682B4FF};
static constexpr Color TAN                     {0xD2B48CFF};
static constexpr Color TEAL                    {0x008080FF};
static constexpr Color THISTLE                 {0xD8BFD8FF};
static constexpr Color TOMATO                  {0xFF6347FF};
static constexpr Color TURQUOISE               {0x40E0D0FF};
static constexpr Color VIOLET                  {0xEE82EEFF};
static constexpr Color WHEAT                   {0xF5DEB3FF};
static constexpr Color WHITE                   {0xFFFFFFFF};
static constexpr Color WHITE_SMOKE             {0xF5F5F5FF};
static constexpr Color YELLOW                  {0xFFFF00FF};
static constexpr Color YELLOW_GREEN            {0x9ACD32FF};
} // namespace colors

} // namespace css
} // namespace strg

#endif //STRUGGLE_COLOR_H
