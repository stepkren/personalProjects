package cz.cvut.fit.tjv.reservationdatabase.controller.dto;

import lombok.AllArgsConstructor;
import lombok.Getter;

import java.util.List;

@Getter
@AllArgsConstructor
public class CuisineDTO {
    private final Long cuisineId;

    private final String country;

    private final List<Long> restaurantIds;
}
