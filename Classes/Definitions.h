//
//  Definitions.h
//  jumpii
//
//  Created by Jose Castellanos on 10/18/14.
//
//

#ifndef jumpii_Definitions_h
#define jumpii_Definitions_h

#define TRANSITION_TIME 0.5f

#define SCORES_DATA_KEY "SCORES"

#define RABBIT_COLLISION_BITMASK 0x000001
#define EDGE_COLLISION_BITMASK 0x000002
#define NO_PLATFORM_COLLISION_BITMASK 0x000003

#define PLATFORM_HEIGHT 450
#define PLATFORM_HEIGHT_GAP 150
#define PLATFORM_HEIGHT_GAP_2 50
#define PLATFORM_WIDTH 320
#define BACKGROUND_WIDTH 2560

#define TOTAL_PLATFORMS 8

#define INITIAL_RANDOM_CLOUDS_COUNT 5+arc4random()%5
#define LATER_RANDOM_CLOUDS_COUNT 3+arc4random()%5
#define ADDING_CLOUDS_TIME 15.0f

#define BACKGROUND_MOVEMENT 256
#define MOVE_BACKGROUND_TIME 20.0f

#endif
