package cz.cvut.fit.tjv.reservationdatabase.controller.converter;

import cz.cvut.fit.tjv.reservationdatabase.application.RestaurantServiceInterface;
import cz.cvut.fit.tjv.reservationdatabase.controller.dto.CustomerDTO;
import cz.cvut.fit.tjv.reservationdatabase.domain.Customer;
import cz.cvut.fit.tjv.reservationdatabase.domain.Restaurant;
import org.springframework.stereotype.Component;

import java.util.Collection;
import java.util.Collections;
import java.util.List;

@Component
public class CustomerDTOConverter implements DTOConverter<CustomerDTO, Customer>{

    private final RestaurantServiceInterface restaurantService;

    public CustomerDTOConverter (RestaurantServiceInterface restaurantService) {
        this.restaurantService = restaurantService;
    }

    @Override
    public CustomerDTO toDTO (Customer customer) {
        return new CustomerDTO(
                customer.getCustomerId(),
                customer.getName(),
                customer.getPhoneNumber(),
                customer.getEmail(),
                customer.getVisited().stream().map(Restaurant::getRestaurantId).toList()
        );
    }

    @Override
    public Customer toEntity (CustomerDTO customerDTO) {
        Customer customer = new Customer();
        customer.setCustomerId(customerDTO.getCustomerId());
        customer.setName(customerDTO.getName());
        customer.setPhoneNumber(customerDTO.getPhoneNumber());
        customer.setEmail(customerDTO.getEmail());

        List<Long> restaurantIds = customerDTO.getRestaurantIds();
        if(restaurantIds != null && restaurantIds.isEmpty()) {
            List<Restaurant> visitedRestaurants = customerDTO.getRestaurantIds().stream().map(restaurantService::getRestaurantById).toList();
            customer.setVisited(visitedRestaurants);
        } else {
            customer.setVisited(Collections.emptyList());
        }

        return customer;
    }
}
