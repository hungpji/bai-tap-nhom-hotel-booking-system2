FROM gcc:latest
WORKDIR /usr/src/app
COPY . .
RUN g++ -o hotel_app main.cpp HotelSystem.cpp
CMD ["./hotel_app"]