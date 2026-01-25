# HMP Files

This stuff is well covered by the [ReRogue's spec file](https://github.com/dpethes/rerogue/blob/master/doc/file_hmp_spec.txt).
As such this file's purpose is to be a slightly more verbose explanation of the details found there.

## File Header

The file starts with a header-like section, specifying a bunch of global settings and offsets to other bits of data.

```cpp
struct hmp_header {
    // ReRogue suggests these are always 0 which seems plausible
    // They are read and saved in `load_level_hmp.c`, and those saved values are referenced elsewhere, but their use is unknown
    /* 0x00 */ f32 floats[3];
    // I wonder if these are meant to be X/Y/Z scales.
    // If that's correct, only the Y scale (height_scale) is read/used by the game, the other 2 go entirely unused
    /* 0x0C */ f32 always_half;
    /* 0x10 */ f32 height_scale;
    /* 0x14 */ f32 always_half2;
    /* 0x18 */ u16 tile_count;
    /* 0x1A */ u16 texture_count;
    /* 0x1C */ u32 tile_offset; // File relative!
    /* 0x20 */ u32 lighting_offset; // File relative!
    /* 0x24 */ u16 width;
    /* 0x26 */ u16 height;
}; // size = 0x28
```

## Tile Indices

After the header is an array of `u16`s.
Presumably this is something akin to the color indices in a palletted imaged; rather than having a bunch of repeated information, you have 1 copy of each "tile" and then have as many references to it as you want in this array.

The game code suggests that the top 3 bits of the `u16` are used as bit-flags.
Everytime a value from this list is used to access the tile array proper it gets and'd with `0x1FFF`.
I have no idea what the bit-flags represent though, and presumably they are all 0 in the `hmp` file itself.

## Lighting Data

After the tile indices there's some lighting data.

There' 3 words worth of a header-like section for the lighting data, with the data proper coming after.

ReRogue puts the header-like data into the first, "global", lighitng object, but I think that's wrong.
Or, at least, the game does something slightly goofy that makes the game's code hard to line up with what ReRogue says.
The 2 colors the ReRogue identifies are handled separately from all the light objects (global or otherwise).
I can't quite tell what's going on, but I don't *think* the game treats the global object any different from the other light objects.
But its hard to tell what's going on in the raw decomp output though.
There's definitely some type of special handling going on but I think its for handling inactive lights across the board, which the global object happens to be one of.

```cpp
struct lighting_data {
    /* 0x00 */ u32 light_object_count; // This is the number of `light_object`s + the `global_terrain_light_object`
    /* 0x04 */ rgba terrain_shadow_color;
    /* 0x08 */ rgba world_light_color;

    struct global_terrain_light_object {
    /* 0x0C / 0x00 */ f32 rgb_intensity[3];
    /* 0x18 / 0x0C */ u8 active;
    /* 0x19 / 0x0D */ u8 mode;
    /* 0x1A / 0x0E */ u8 intesity_boost;
    /* 0x1B / 0x0F */ u8 unk0F;
    // As ReRogue suggests, this is always normalized. Which makes it extra funny that the game normalizes it upon ingestion too
    /* 0x1C / 0x10 */ f32 light_direction[3];
    /* 0x28 / 0x1C */ f32 unk24;
    }; // size 0x20

    struct light_object {
    /* 0x2C / 0x00 */ f32 rgb_intensity[3];
    /* 0x38 / 0x0C */ u8 active;
    /* 0x39 / 0x0D */ u8 mode;
    /* 0x3A / 0x0E */ u8 intesity_boost;
    /* 0x3B / 0x0F */ u8 unk0F;
    /* 0x3C / 0x10 */ f32 location[3];
    /* 0x48 / 0x1C */ f32 size_scale;
    }; // size = 0x20
}
```

## Tiles

And finally there's the tiles themselves.
As noted by ReRogue, they are followed by 2 bytes of zeros.
I can't say I rightfully understand why though.
The game code doesn't use the zero's as a end-of-list marker, which is the only practical purpose that I can think of.
I guess it could be padding, rather than something done on purpose by the developers.

Something that ReRogue doesn't mention, and took me awhile to notice on my own, is that the height values are signed values.
Or, at the very least, I think they are.
If you treat them as unsigned bytes, you end up in situations where the minimum height is larger than the maximum height

```cpp
struct hmp_tile {
    /* 0x00 */ u16 texmap_idx;
    /* 0x02 */ u8 flags;
    /* 0x03 */ s8 min_height;
    /* 0x04 */ s8 max_height;
    /* 0x05 */ s8 height_values[25];
}; // size 0x1E
```

## Utility Programs

I've made a couple utility functions for dealing with HMP files.
[hmp_parse.c](./docs/hmp_files/hmp_parse.c) Presents the HMP data in a more human-redable format, while [hmp_to_png.c](./docs/hmp_files/hmp_to_png.c) takes the height data and turns it into a png file.
I'm probably doing something wrong the PNG conversion though, the images come out updside down.
