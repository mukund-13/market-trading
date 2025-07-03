#include "../include/networking/Server.hpp"

Server::Server(boost::asio::io_context& io_context, short port)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
    acceptConnection();
}

void Server::acceptConnection() {
    auto socket = std::make_shared<tcp::socket>(acceptor_.get_executor());
    acceptor_.async_accept(*socket, [this, socket](boost::system::error_code ec) {
        if (!ec) {
            std::cout << "New client connected!" << std::endl;
            std::thread(&Server::handleClient, this, socket).detach();
        }
        acceptConnection();
    });
}

void Server::handleClient(std::shared_ptr<tcp::socket> socket) {
    try {
        boost::asio::streambuf buffer;
        while (true) {
            boost::asio::read_until(*socket, buffer, "\n");
            std::istream inputStream(&buffer);
            std::string clientRequest;
            std::getline(inputStream, clientRequest);

            if (!clientRequest.empty()) {
                std::cout << "Received request: " << clientRequest << std::endl;
                nlohmann::json requestJson = nlohmann::json::parse(clientRequest);

                // Example: Process the request (e.g., fetch market data or place an order)
                std::string response = processRequest(requestJson);
                boost::asio::write(*socket, boost::asio::buffer(response + "\n"));
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Client disconnected: " << e.what() << std::endl;
    }
}

std::string Server::processRequest(const nlohmann::json& request) {
    std::string response;
    try {
        // Handle different types of requests (e.g., market data or order placement)
        if (request["type"] == "fetch_market_data") {
            response = handleMarketDataRequest(request);
        } else if (request["type"] == "place_order") {
            response = handleOrderRequest(request);
        }
    } catch (const std::exception& e) {
        response = "Error processing request: " + std::string(e.what());
    }
    return response;
}

std::string Server::handleMarketDataRequest(const nlohmann::json& request) {
    // Fetch market data (to be integrated with MarketDataHandler)
    std::string symbol = request["symbol"];
    return "Market data for " + symbol;
}

std::string Server::handleOrderRequest(const nlohmann::json& request) {
    // Parse order details and add it to the order book
    Order<double> order;
    order.id = request["order_id"];
    order.isBuyOrder = request["is_buy_order"];
    order.quantity = request["quantity"];
    order.price = request["price"];
    
    orderBook.AddOrder(order.id, order.quantity, order.price, order.isBuyOrder);
    matcher.MatchOrders(orderBook);
    
    return "Order placed successfully.";
}