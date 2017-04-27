require 'sinatra'
require 'mongoid'
require 'slim'
require 'redcarpet'

configure do
  Mongoid.load!("./mongoid.yml")
  enable :sessions
end

class Movie
  def make_permalink
    title.downcase.gsub(/W/,'-').squeeze('-').chomp('-') if title
  end

  include Mongoid::Document

  field :title,     type: String
  field :content,   type: String
  field :trailer,   type: String
  field :poster,    type: String
  field :seen,      type: Integer
  field :director,  type: String
  field :writer,    type: String
  field :imdb,      type: String
  field :permalink, type: String, default: -> { make_permalink }

  index({ title: 'text' })
  scope :title,    -> (title)    { where(title: /#{title}/i)       }
  scope :director, -> (director) { where(director: /#{director}/i) }
  scope :writer,   -> (writer)   { where(writer: /#{writer}/i)     }
end

helpers do
  def url_for movie
    if admin?
      "/movies/" + movie.id
    else
      "/" + movie.permalink   
    end  
  end

  def admin?
    session[:admin]
  end

  def protected!
    halt 401,"You are not authorized to see this page!" unless admin?
  end
end

get '/movies' do
  @movies = Movie.all
  @title = "Some movies list"
  slim :index
end

get '/movies/search' do
  @title = "Results for search"
  @movies = Movie.send(:title,    params[:tsearch]) if params[:tsearch]
  @movies += Movie.send(:director, params[:tsearch]) if params[:tsearch]
  @movies += Movie.send(:writer,   params[:tsearch]) if params[:tsearch]
  @movies = @movies.uniq
  slim :index
end

get '/movies/new' do
  protected!
  @movie = Movie.new
  slim :new
end

get '/movies/:id/edit' do
  protected!
  @movie = Movie.find(params[:id])
  slim :edit
end

get '/movies/:id' do
  @movie = Movie.find(params[:id])
  @movie.update_attributes(seen: @movie.seen + 1)
  @title = @movie.title
  slim :show
end

post '/movies' do
  protected!
  movie = Movie.create(params[:movie])
  movie.update_attributes(seen: 0)
  redirect to("/movies/#{movie.id}")
end

put '/movies/:id' do
  protected!
  movie = Movie.find(params[:id])
  movie.update_attributes(params[:movie])
  redirect to("/movies/#{movie.id}")
end

get '/movies/delete/:id' do
  protected!
  @movie = Movie.find(params[:id])
  slim :delete
end

delete '/movies/:id' do
  protected!
  Movie.find(params[:id]).destroy
  redirect to('/movies')
end

get '/:permalink' do
  begin
    @movie = Movie.find_by(permalink: params[:permalink])
    @movie.update_attributes(seen: @movie.seen + 1)
  rescue
    pass
  end
  slim :show
end

get '/styles/main.css' do
  scss :styles 
end

get '/login' do 
  session[:admin]=true;
  redirect back
end

get '/logout' do 
  session[:admin]=nil;
  redirect back
end

