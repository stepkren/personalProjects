package cz.cvut.fit.tjv.reservationdatabase.controller.converter;

import cz.cvut.fit.tjv.reservationdatabase.application.RestaurantServiceInterface;
import cz.cvut.fit.tjv.reservationdatabase.controller.dto.CuisineDTO;
import cz.cvut.fit.tjv.reservationdatabase.domain.Cuisine;
import cz.cvut.fit.tjv.reservationdatabase.domain.Restaurant;
import org.springframework.stereotype.Component;

import java.util.Collections;
import java.util.List;

@Component
public class CuisineDTOConverter implements DTOConverter<CuisineDTO, Cuisine> {

    private final RestaurantServiceInterface restaurantService;

    public CuisineDTOConverter (RestaurantServiceInterface restaurantService) {
        this.restaurantService = restaurantService;
    }

    @Override
    public CuisineDTO toDTO(Cuisine cu) {
        return new CuisineDTO(
                cu.getCuisineId(),
                cu.getCountry(),
                cu.getIsCookedAt().stream().map(Restaurant::getRestaurantId).toList()
        );
    }

    @Override
    public Cuisine toEntity(CuisineDTO cuisineDTO) {
        Cuisine cuisine = new Cuisine();
        cuisine.setCuisineId(cuisineDTO.getCuisineId());
        cuisine.setCountry(cuisineDTO.getCountry());

        List<Long> restaurantIds = cuisineDTO.getRestaurantIds();
        if(restaurantIds != null && restaurantIds.isEmpty()) {
            List<Restaurant> cookedAt = cuisineDTO.getRestaurantIds().stream().map(restaurantService::getRestaurantById).toList();
            cuisine.setIsCookedAt(cookedAt);
        } else {
            cuisine.setIsCookedAt(Collections.emptyList());
        }

        return cuisine;
    }
}
