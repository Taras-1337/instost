#include "radar.h"

#include <math.h>
#include <stdio.h>

#include "../interfaces.h"
#include "../math.h"

#include "../SDK/IEngineVGui.h"
#include "../SDK/IEngineClient.h"
#include "../SDK/IClientEntity.h"
#include "../SDK/IClientEntityList.h"

void
draw_player(const vector2 *pos, int r, int g, int b, int fy);

void
hk_radar(void *local_player, int width, int height)
{
    vector3 player_pos;
    vector3 remote_player_pos;
    vector2 radar_player_pos;
    vector2 radar_pos = { (float) width / 2 - (float) RADAR_SIZE / 2, 0 };
    vector3 player_view;
    float dx;
    float dy;
    float fy;

    float min_x_pos;
    float max_x_pos;
    float min_z_pos;
    float max_z_pos;
    float min_radar_pos = 5;
    float max_radar_pos = RADAR_SIZE - 5;

    /* Draw radar plot */
    draw_set_color(surface, 0, 85, 0, 85);
    draw_filled_rect(surface, radar_pos.x, radar_pos.y, radar_pos.x + RADAR_SIZE, radar_pos.y + RADAR_SIZE);
    draw_set_color(surface, 255, 0, 0, 255);
    draw_outlined_rect(surface, radar_pos.x, radar_pos.y, radar_pos.x + RADAR_SIZE, radar_pos.y + RADAR_SIZE);

    /* Local player on radar */
    player_pos = get_pos_origin(local_player);
    radar_player_pos.x = radar_pos.x + (float) RADAR_SIZE / 2;
    radar_player_pos.y = radar_pos.y + (float) RADAR_SIZE / 2;
    draw_player(&radar_player_pos, 255, 255, 255, 0);

    /* Local player's rotation */
    get_view_angles(engine, &player_view);
    dx = RADAR_YAW_LINE * sin(player_view.y * M_PI / 180);
    dy = RADAR_YAW_LINE * cos(player_view.y * M_PI / 180);
    vector2 yaw_points[2] =
    {
        {
            radar_player_pos.x - 1,
            radar_player_pos.y - 1
        },
        {
            radar_player_pos.x + dx,
            radar_player_pos.y + dy
        }
    };
    draw_set_color(surface, 255, 0, 255, 255);
    draw_line(surface,
        yaw_points[0].x,
        yaw_points[0].y,
        yaw_points[1].x,
        yaw_points[1].y);

    min_x_pos = player_pos.x - ((float) RADAR_RANGE / 2);
    max_x_pos = player_pos.x + ((float) RADAR_RANGE / 2);
    min_z_pos = player_pos.y - ((float) RADAR_RANGE / 2);
    max_z_pos = player_pos.y + ((float) RADAR_RANGE / 2);

    for (int i = 0; i <= get_max_clients(engine); ++i) {
        void *player = get_client_entity(entity_list, i);
        if (!player || player == local_player) {
            continue;
        }

        bool alive = is_alive(player);
        bool dormant = is_dormant(player);
        bool same_team = get_team_num(player) == get_team_num(local_player);

        if (!alive) {
            continue;
        }
        remote_player_pos = get_pos_origin(player);

        if (remote_player_pos.x > max_x_pos || remote_player_pos.x < min_x_pos) {
            continue;
        }

        if (remote_player_pos.y > max_z_pos || remote_player_pos.y < min_z_pos) {
            continue;
        }

        /* NOTE: Y and Z are inverted (Yet another total zrada) */
        radar_player_pos.x =
            radar_pos.x
            + ((remote_player_pos.x - min_x_pos)
               / (max_x_pos - min_x_pos))
            * (max_radar_pos - min_radar_pos)
            + min_radar_pos;
        radar_player_pos.y =
            radar_pos.y
            + ((remote_player_pos.y - min_z_pos)
               / (max_z_pos - min_z_pos))
            * (max_radar_pos - min_radar_pos)
            + min_radar_pos;

        fy = 0;
        if (remote_player_pos.z < player_pos.z - RADAR_PLAYER_FLOOR) {
            fy = -1;
        } else if (remote_player_pos.z > player_pos.z + RADAR_PLAYER_FLOOR) {
            fy = 1;
        }

        if (dormant) {
            draw_player(&radar_player_pos, 71, 71, 71, fy);
        } else if (same_team) {
            draw_player(&radar_player_pos, 0, 183, 255, fy);
        } else {
            draw_player(&radar_player_pos, 255, 200, 0, fy);
        }
    }
}

void
draw_player(const vector2 *pos, int r, int g, int b, int fy)
{
    vector2 rect = {
        pos->x - ((float) RADAR_PLAYER_SIZE / 2),
        pos->y - ((float) RADAR_PLAYER_SIZE / 2)
    };
    vector2 left_floor_points[2] =
    {
        { rect.x - 1,
          (fy > 0 ? rect.y : rect.y + RADAR_PLAYER_SIZE - 1)
        },
        { rect.x + (float) RADAR_PLAYER_SIZE / 2 - 2,
          (fy > 0 ? rect.y - 5 : rect.y + RADAR_PLAYER_SIZE + 5)
        }
    };
    vector2 right_floor_points[2] =
    {
        { rect.x - 1 + RADAR_PLAYER_SIZE,
          (fy > 0 ? rect.y : rect.y + RADAR_PLAYER_SIZE - 1)
        },
        { rect.x + (float) RADAR_PLAYER_SIZE / 2 - 2,
          (fy > 0 ? rect.y - 6 : rect.y + RADAR_PLAYER_SIZE + 5)
        }
    };

    draw_set_color(surface, r, g, b, 255);
    draw_filled_rect(surface, rect.x, rect.y, rect.x + RADAR_PLAYER_SIZE, rect.y + RADAR_PLAYER_SIZE);

    if (fy) {
        draw_line(surface,
                  left_floor_points[0].x,
                  left_floor_points[0].y,
                  left_floor_points[1].x,
                  left_floor_points[1].y);
        draw_line(surface,
                  right_floor_points[0].x,
                  right_floor_points[0].y,
                  right_floor_points[1].x,
                  right_floor_points[1].y);
    }
}
