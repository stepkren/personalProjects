package cz.cvut.fit.tjv.reservationdatabase.controller.dto;

import lombok.AllArgsConstructor;
import lombok.Getter;

import java.util.Date;
import java.util.List;

@Getter
@AllArgsConstructor
public class RestaurantDTO {
    private final Long restaurantId;

    private final String name;

    private final String phoneNumber;

    private final Date openFrom;

    private final Long itemsOnMenu;

    private final Long cooksId;

    private final List<Long> visitedByIds;
}
