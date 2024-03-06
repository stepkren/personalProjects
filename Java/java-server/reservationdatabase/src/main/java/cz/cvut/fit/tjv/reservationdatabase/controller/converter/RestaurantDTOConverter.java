package cz.cvut.fit.tjv.reservationdatabase.controller.converter;

import cz.cvut.fit.tjv.reservationdatabase.application.CuisineServiceInterface;
import cz.cvut.fit.tjv.reservationdatabase.application.CustomerServiceInterface;
import cz.cvut.fit.tjv.reservationdatabase.controller.dto.RestaurantDTO;
import cz.cvut.fit.tjv.reservationdatabase.domain.Customer;
import cz.cvut.fit.tjv.reservationdatabase.domain.Restaurant;
import org.springframework.stereotype.Component;

import java.util.Collection;
import java.util.Collections;
import java.util.List;
import java.util.Optional;

@Component
public class RestaurantDTOConverter implements DTOConverter<RestaurantDTO, Restaurant>{

    private final CustomerServiceInterface customerService;

    private final CuisineServiceInterface cuisineService;

    public RestaurantDTOConverter (CustomerServiceInterface customerService, CuisineServiceInterface cuisineService) {
        this.customerService = customerService;
        this.cuisineService = cuisineService;
    }

    @Override
    public RestaurantDTO toDTO(Restaurant rest) {
        return new RestaurantDTO(
                rest.getRestaurantId(),
                rest.getName(),
                rest.getPhoneNumber(),
                rest.getOpenFrom(),
                rest.getItemsOnMenu(),
                rest.getCooks().getCuisineId(),
                rest.getVisitedBy().stream().map(Customer::getCustomerId).toList()
        );
    }

    @Override
    public Restaurant toEntity(RestaurantDTO restDTO) {
        Restaurant restaurant = new Restaurant();
        restaurant.setRestaurantId(restDTO.getRestaurantId());
        restaurant.setName(restDTO.getName());
        restaurant.setPhoneNumber(restDTO.getPhoneNumber());
        restaurant.setOpenFrom(restDTO.getOpenFrom());
        restaurant.setItemsOnMenu(restDTO.getItemsOnMenu());
        restaurant.setCooks(cuisineService.getCuisineById(restDTO.getCooksId()));

        List<Long> customerIds = restDTO.getVisitedByIds();
        if (customerIds != null && customerIds.isEmpty() ) {
            List<Customer> visitedBy = restDTO.getVisitedByIds().stream().map(customerService::getCustomerById).toList();
            restaurant.setVisitedBy(visitedBy);
        } else {
            restaurant.setVisitedBy(Collections.emptyList());
        }

        return restaurant;
    }
}
