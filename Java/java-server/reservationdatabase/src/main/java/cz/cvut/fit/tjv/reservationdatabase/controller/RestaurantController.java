package cz.cvut.fit.tjv.reservationdatabase.controller;

import cz.cvut.fit.tjv.reservationdatabase.application.CuisineServiceInterface;
import cz.cvut.fit.tjv.reservationdatabase.application.CustomerServiceInterface;
import cz.cvut.fit.tjv.reservationdatabase.application.RestaurantServiceInterface;
import cz.cvut.fit.tjv.reservationdatabase.controller.converter.DTOConverter;
import cz.cvut.fit.tjv.reservationdatabase.controller.dto.CuisineDTO;
import cz.cvut.fit.tjv.reservationdatabase.controller.dto.CustomerDTO;
import cz.cvut.fit.tjv.reservationdatabase.controller.dto.RestaurantDTO;
import cz.cvut.fit.tjv.reservationdatabase.domain.Cuisine;
import cz.cvut.fit.tjv.reservationdatabase.domain.Customer;
import cz.cvut.fit.tjv.reservationdatabase.domain.Restaurant;
import io.swagger.v3.oas.annotations.Operation;
import io.swagger.v3.oas.annotations.responses.ApiResponse;
import io.swagger.v3.oas.annotations.responses.ApiResponses;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/rest/api/restaurant")
public class RestaurantController {

    private final CustomerServiceInterface customerService;

    private final CuisineServiceInterface cuisineService;

    private final RestaurantServiceInterface restaurantService;

    private final DTOConverter<CustomerDTO, Customer> customerDTOConverter;

    private final DTOConverter<CuisineDTO, Cuisine> cuisineDTOConverter;

    private final DTOConverter<RestaurantDTO, Restaurant> restaurantDTOConverter;

    private RestaurantController (CustomerServiceInterface customerService, CuisineServiceInterface cuisineService, RestaurantServiceInterface restaurantService,
                                DTOConverter<CuisineDTO, Cuisine> cuisineDTOConverter,
                                DTOConverter<RestaurantDTO, Restaurant> restaurantDTOConverter,
                                DTOConverter<CustomerDTO, Customer> customerDTOConverter) {
        this.customerService = customerService;
        this.cuisineService = cuisineService;
        this.restaurantService = restaurantService;
        this.customerDTOConverter = customerDTOConverter;
        this.cuisineDTOConverter = cuisineDTOConverter;
        this.restaurantDTOConverter = restaurantDTOConverter;
    }

    @Operation(summary = "Gets all restaurants")
    @ApiResponses(value = {
            @ApiResponse(responseCode = "200", description = "Successfully retrieved list of restaurants")
    })
    @GetMapping
    public List<RestaurantDTO> getRestaurants() {
        return restaurantService.getRestaurants().stream().map(restaurantDTOConverter::toDTO).toList();
    }

    @Operation(summary = "Gets restaurant specified by id")
    @ApiResponses(value = {
            @ApiResponse(responseCode = "200", description = "Successfully retrieved restaurant"),
            @ApiResponse(responseCode = "404", description = "Restaurant not found")
    })
    @GetMapping(path = "{id}")
    public RestaurantDTO getRestaurant(@PathVariable("id") Long id) {
        return restaurantDTOConverter.toDTO(restaurantService.getRestaurantById(id));
    }

    @Operation(summary = "Gets all customers that visited restaurant specified by id")
    @ApiResponses(value = {
            @ApiResponse(responseCode = "200", description = "Successfully retrieved list of customers"),
            @ApiResponse(responseCode = "404", description = "Restaurant not found")
    })
    @GetMapping(path = "{id}/visitedBy")
    public List<CustomerDTO> getVisitingCustomers (@PathVariable("id") Long id) {
        return restaurantService.getRestaurantById(id).getVisitedBy().stream().map(customerDTOConverter::toDTO).toList();
    }

    @Operation(summary = "Gets cuisine cooked at restaurant specified by id")
    @ApiResponses(value = {
            @ApiResponse(responseCode = "200", description = "Successfully retrieved cuisine"),
            @ApiResponse(responseCode = "404", description = "Restaurant not found")
    })
    @GetMapping(path = "{id}/cooks")
    public CuisineDTO getRestaurantsCuisine (@PathVariable("id") Long id) {
        return cuisineDTOConverter.toDTO(restaurantService.getRestaurantById(id).getCooks());
    }

    @Operation(summary = "Adds cuisine to restaurant")
    @ApiResponses(value = {
            @ApiResponse(responseCode = "200", description = "Successfully added cuisine to restaurant"),
            @ApiResponse(responseCode = "400", description = "Invalid cuisine or restaurant id given")
    })
    @PostMapping(path = "{id}/cooks")
    public RestaurantDTO addCuisineToRestaurant (@RequestBody Long cuisineId, @PathVariable("id") Long restaurantId) {
        restaurantService.addCuisineToRestaurant(cuisineId, restaurantId);
        return restaurantDTOConverter.toDTO(restaurantService.getRestaurantById(restaurantId));
    }

    @Operation(summary = "Removes cuisine from restaurant")
    @ApiResponses(value = {
            @ApiResponse(responseCode = "200", description = "Successfully removed cuisine from restaurant"),
            @ApiResponse(responseCode = "400", description = "Invalid restaurant id given")
    })
    @DeleteMapping(path = "{restaurantId}/cooks")
    public void removeCuisineFromRestaurant (@PathVariable("restaurantId") Long restaurantId) {
        restaurantService.removeCuisineFromRestaurant(restaurantId);
    }

    @Operation(summary = "Creates a new restaurant")
    @ApiResponses(value = {
            @ApiResponse(responseCode = "200", description = "Successfully created new restaurant"),
            @ApiResponse(responseCode = "400", description = "Invalid phone number given")
    })
    @PostMapping
    public RestaurantDTO createRestaurant(@RequestBody RestaurantDTO r) {
        return restaurantDTOConverter.toDTO(restaurantService.createRestaurant(restaurantDTOConverter.toEntity(r)));
    }

    @Operation(summary = "Updates existing restaurant")
    @ApiResponses(value = {
            @ApiResponse(responseCode = "200", description = "Successfully updated restaurant"),
            @ApiResponse(responseCode = "400", description = "Invalid restaurant given")
    })
    @PutMapping(path = "{id}")
    public RestaurantDTO updateRestaurant(@PathVariable Long id, @RequestBody RestaurantDTO r) {
        Restaurant restaurantEntity = restaurantDTOConverter.toEntity(r);
        restaurantEntity.setRestaurantId(id);
        return restaurantDTOConverter.toDTO(restaurantService.updateRestaurant(restaurantEntity));
    }

    @Operation(summary = "Deletes existing restaurant")
    @ApiResponses(value = {
            @ApiResponse(responseCode = "200", description = "Successfully deleted restaurant"),
            @ApiResponse(responseCode = "404", description = "Restaurant not found")
    })
    @DeleteMapping(path = "{id}")
    public void deleteRestaurant (@PathVariable Long id) {
        restaurantService.deleteRestaurant(id);
    }
}
